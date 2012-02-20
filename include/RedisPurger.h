#ifndef fastpurge_RedisPurger_h
#define fastpurge_RedisPurger_h

#define FNORDCAST1 (void (*)(const redisAsyncContext*, int))
#define FNORDCAST2 (void (*)(redisAsyncContext*, void*, void*))

#define REDIS_KEYMODE_GLOB 0
#define REDIS_KEYMODE_HDEL 1
#define REDIS_KEYMODE_SDEL 2
#define REDIS_KEYMODE_ZDEL 3

#include <signal.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libev.h>

#include "fastpurge.h"
#include "BaseAdapter.h"

class RedisPurger : public BaseAdapter {
protected:
	redisAsyncContext* redis;
	int redisKeyMode;
	char* redisKeyString;

public:
	RedisPurger(ev::loop_ref& loop_, const char* address_);
	void setOption(char opt, char* value);
	void purge();
	void purgeWithoutRegex();
	void purgeWithRegex();	
	void purgeKey(std::string key);
	void purgeMatchingKeys(void* keys);	

	static void onKeydata(redisAsyncContext *redis, void *response, void *privdata);
	static void onConnect(const redisAsyncContext* redis, int status);
	static void onDisconnect(const redisAsyncContext* redis, int status);	
};

#endif
