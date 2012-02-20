#include "fastpurge.h"
#include "RedisPurger.h"

RedisPurger::RedisPurger(ev::loop_ref& loop_, char const *address_) : BaseAdapter(loop_, address_) {
	printf("redispurger initialized: %s -> %i \n", this->address, dry_run);
}

void RedisPurger::purge() {
	printf("let's go!\n");

	/* FIXPAUL: use ip port from this->address */
	redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);

	if (c->err) {
		printf("can't connect to redis %s - %s\n", this->address, c->errstr);
		exit(1);
	}
	if (!use_regex) {
			
		for(auto& pattern: this->string_patterns){
			if (!silent)
			  printf("delete key: %s\n", pattern.c_str());				

			redisAsyncCommand(c, NULL, NULL, "DEL %s",  pattern.c_str(), pattern.length()); 
		}

	} else {
		/* we need to get a list of keys from redis first */
		printf("get redis keys\n");
	}
}
