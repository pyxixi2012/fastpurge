#include "fastpurge.h"
#include "RedisPurger.h"

RedisPurger::RedisPurger(ev::loop_ref& loop_, char const *address_) : BaseAdapter(loop_, address_) {
	this->redisKeyMode = REDIS_KEYMODE_GLOB;

	/* FIXPAUL: use ip port from this->address */
	this->redis = redisAsyncConnect("127.0.0.1", 6379);			
	redisLibevAttach(this->loop, this->redis);

	/* FIXPAUL: this is ugly */
	redisAsyncSetConnectCallback(this->redis, FNORDCAST1 &RedisPurger::onConnect);    
	redisAsyncSetDisconnectCallback(this->redis, FNORDCAST1 &RedisPurger::onDisconnect);    

	if (redis->err) {		
		printf("ERROR: %s\n", this->redis->errstr);	
		exit(1);
	}
}

void RedisPurger::setOption(char opt, char* value){
	switch (opt) {

		case OPT_HDEL:
			this->redisKeyMode = REDIS_KEYMODE_HDEL;
			this->redisKeyString = value;
			break;

		case OPT_SDEL:
			this->redisKeyMode = REDIS_KEYMODE_SDEL;
			this->redisKeyString = value;
			break;

		case OPT_ZDEL:
			this->redisKeyMode = REDIS_KEYMODE_ZDEL;
			this->redisKeyString = value;
			break;

	}
}

void RedisPurger::purge() {	
	if (use_regex) {			
		purgeWithRegex();
	} else {
		purgeWithoutRegex();
	}
}

void RedisPurger::purgeWithoutRegex() {
	for(auto& pattern: this->string_patterns){
		if (!silent)
			printf("delete key: %s\n", pattern.c_str());				

		if (!dry_run)
			purgeKey(pattern);
	}
}

void RedisPurger::purgeWithRegex() {	
	printf("getting list of keys from redis %s\n", this->address);
	/* FIXPAUL: implement hdel/zdel/sdel, also this line is ugly... */
	redisAsyncCommand(this->redis, FNORDCAST2&RedisPurger::onKeydata, this, "KEYS *");
}

void RedisPurger::purgeMatchingKeys(void* keys_ptr) {
	redisReply *keys = (redisReply*)keys_ptr;
	for (unsigned int i = 0; i < keys->elements; i++){ 
		for(auto& pattern: this->regex_patterns){
			int match = !regexec(&pattern, keys->element[i]->str, 0, NULL, 0);

			if(match && !silent)
				printf("delete key: %s\n", keys->element[i]->str);	
			
			if(match && !dry_run)
				purgeKey(keys->element[i]->str);		
		}		
	}
}

void RedisPurger::purgeKey(std::string key) {
	switch (this->redisKeyMode) {
		case REDIS_KEYMODE_GLOB:
			printf("glob delete\n");
			break;
		case REDIS_KEYMODE_HDEL:
			printf("hdel delete\n");
			break;
	}
	/* FIXPAUL: implement hdel/zdel/sdel */
	redisAsyncCommand(this->redis, NULL, NULL, "DEL %s",  key.c_str(), key.length()); 
}

void RedisPurger::onKeydata(redisAsyncContext *redis, void* response, void* privdata) {
	RedisPurger *self = reinterpret_cast<RedisPurger *>(privdata);	
	self->purgeMatchingKeys(response);  
}

void RedisPurger::onConnect(const redisAsyncContext* redis, int status) {
	if (status != REDIS_OK) {
		printf("ERROR: %s\n", redis->errstr);
		return;
	}
	/* FIXPAUL: print connection successful with server addr */
	printf("Connected...\n");
}

void RedisPurger::onDisconnect(const redisAsyncContext* redis, int status) {
	if (status != REDIS_OK) {
		printf("ERROR: %s\n", redis->errstr);
		return;
	}	
	/* FIXPAUL: print connection failed with server addr */
	printf("Disconnected...\n");
}