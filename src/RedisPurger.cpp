#include "fastpurge.h"
#include "RedisPurger.h"

RedisPurger::RedisPurger(ev::loop_ref& loop_, char const *address_) : BaseAdapter(loop_, address_) {
	/* FIXPAUL: use ip port from this->address */
	this->redis = redisAsyncConnect("127.0.0.1", 6379);		
	redisLibevAttach(this->loop, this->redis);

	/* FIXPAUL: this is ugly */
	redisAsyncSetConnectCallback(this->redis, (void (*)(const redisAsyncContext*, int))&RedisPurger::onConnect);    
	redisAsyncSetDisconnectCallback(this->redis, (void (*)(const redisAsyncContext*, int))&RedisPurger::onDisconnect);    

	if (redis->err) {		
		printf("ERROR: %s\n", this->redis->errstr);	
		exit(1);
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
	/* FIXPAUL: implement purgeWithRegex */
	printf("regex purge not yet implemented \n");
}

void RedisPurger::purgeKey(std::string key) {
	/* FIXPAUL: implement hdel/zdel/sdel */
	redisAsyncCommand(this->redis, NULL, NULL, "DEL %s",  key.c_str(), key.length()); 
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