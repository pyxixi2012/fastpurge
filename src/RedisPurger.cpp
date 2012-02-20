#include "fastpurge.h"
#include "RedisPurger.h"

RedisPurger::RedisPurger(ev::loop_ref& loop_, char const *address_) : BaseAdapter(loop_, address_) {
	this->redisKeyMode = REDIS_KEYMODE_GLOB;

	/* FIXPAUL: use ip port from this->address */
	this->redis = redisAsyncConnect("127.0.0.1", 6379);			
	redisLibevAttach(this->loop, this->redis);

	redisAsyncSetConnectCallback(this->redis, FNORDCAST1 &RedisPurger::onConnect);    
	redisAsyncSetDisconnectCallback(this->redis, FNORDCAST1 &RedisPurger::onDisconnect);    

	if (redis->err) {		
		printf("ERROR: %s\n", this->redis->errstr);	
		exit(1);
	}
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
}

void RedisPurger::onDisconnect(const redisAsyncContext* redis, int status) {
	if (status != REDIS_OK) {
		printf("ERROR: %s\n", redis->errstr);
		return;
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
	char command[1024];

	switch (this->redisKeyMode) {
		case REDIS_KEYMODE_GLOB:
			snprintf(command, sizeof(command), "KEYS *");
			break;
		case REDIS_KEYMODE_HDEL:
			snprintf(command, sizeof(command), "HKEYS %s", this->redisKeyString);
			break;
		case REDIS_KEYMODE_ZDEL:
			snprintf(command, sizeof(command), "ZRANGE %s 0 -1", this->redisKeyString);
			break;
		case REDIS_KEYMODE_SDEL:
			snprintf(command, sizeof(command), "SMEMBERS %s", this->redisKeyString);
			break;		
	}

	redisAsyncCommand(this->redis, FNORDCAST2&RedisPurger::onKeydata, this, command);
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
	char command[1024];

	switch (this->redisKeyMode) {
		case REDIS_KEYMODE_GLOB:
			snprintf(command, sizeof(command), "DEL %s", key.c_str());
			break;
		case REDIS_KEYMODE_HDEL:
			snprintf(command, sizeof(command), "HDEL %s %s", this->redisKeyString, key.c_str());
			break;
		case REDIS_KEYMODE_ZDEL:
			snprintf(command, sizeof(command), "ZREM %s %s", this->redisKeyString, key.c_str());
			break;
		case REDIS_KEYMODE_SDEL:
			snprintf(command, sizeof(command), "SREM %s %s", this->redisKeyString, key.c_str());
			break;		
	}

	redisAsyncCommand(this->redis, FNORDCAST2&RedisPurger::onKeydata, this, command);
}

