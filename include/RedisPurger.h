#ifndef fastpurge_RedisPurger_h
#define fastpurge_RedisPurger_h

#include <signal.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libev.h>

#include "BaseAdapter.h"

class RedisPurger : public BaseAdapter {

public:
	RedisPurger(ev::loop_ref& loop_, char const *address_);
	void purge();
	void purgeKey(redisAsyncContext *redis, std::string key);
};

#endif
