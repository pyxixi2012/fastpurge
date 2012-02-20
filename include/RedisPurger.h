#ifndef fastpurge_RedisPurger_h
#define fastpurge_RedisPurger_h

#include "BaseAdapter.h"

class RedisPurger : public BaseAdapter {

public:
	RedisPurger(ev::loop_ref& loop_, char const *address_);
	void purge();
};

#endif
