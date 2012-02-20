#ifndef fastpurge_RedisPurger_h
#define fastpurge_RedisPurger_h

#include <signal.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libev.h>

#include "BaseAdapter.h"

class RedisPurger : public BaseAdapter {
protected:
	redisAsyncContext* redis;

public:
	RedisPurger(ev::loop_ref& loop_, const char* address_);
	void purge();
	void purgeWithoutRegex();
	void purgeWithRegex();	
	void purgeKey(std::string key);
	void purgeMatchingKeys(std::vector<std::string> keys);

	static void onConnect(const redisAsyncContext* redis, int status);
	static void onDisconnect(const redisAsyncContext* redis, int status);
	static void onKeydata(const redisAsyncContext* redis, int status);
};

#endif
