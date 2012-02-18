#ifndef fastpurge_RedisPurger_h
#define fastpurge_RedisPurger_h

#include "BaseAdapter.h"

class RedisPurger
	: public BaseAdapter {
private:
	/* Redis specific variables */

public:
	RedisPurger(ev::loop_ref &);

	/* Setter methods */

	void purge();
};

#endif
