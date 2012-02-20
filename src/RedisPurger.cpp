#include "fastpurge.h"
#include "RedisPurger.h"

RedisPurger::RedisPurger(ev::loop_ref& loop_, char const *address_) : BaseAdapter(loop_, address_) {
	printf("redispurger initialized: %s -> %i \n", this->address, dry_run);
}

void RedisPurger::purge() {	
	/* FIXPAUL: use ip port from this->address */
	redisAsyncContext* redis = redisAsyncConnect("127.0.0.1", 6379);		
	redisLibevAttach(this->loop, redis);

	/* FIXPAUL: this is ugly */
	redisAsyncSetConnectCallback(redis, (void (*)(const redisAsyncContext*, int))&RedisPurger::onConnect);    
	redisAsyncSetDisconnectCallback(redis, (void (*)(const redisAsyncContext*, int))&RedisPurger::onDisconnect);    

	if (redis->err) {		
		return;
	}

	if (!use_regex) {
			
		for(auto& pattern: this->string_patterns){
			if (!silent)
				printf("delete key: %s\n", pattern.c_str());				

			purgeKey(redis, pattern);
		}

	} else {

		/* we need to get a list of keys from redis first */
		printf("get redis keys\n");

	}

}

void RedisPurger::purgeKey(redisAsyncContext *redis, std::string key) {
	/* FIXPAUL: implement hdel/zdel/sdel */
	redisAsyncCommand(redis, NULL, NULL, "DEL %s",  key.c_str(), key.length()); 
}

void RedisPurger::onConnect(const redisAsyncContext *redis, int status) {
	if (status != REDIS_OK) {
		printf("ERROR: %s\n", redis->errstr);
		return;
	}
	/* FIXPAUL: print connection successful with server addr */
	printf("Connected...\n");
}

void RedisPurger::onDisconnect(const redisAsyncContext *redis, int status) {
	if (status != REDIS_OK) {
		printf("ERROR: %s\n", redis->errstr);
		return;
	}	
	/* FIXPAUL: print connection failed with server addr */
	printf("Disconnected...\n");
}