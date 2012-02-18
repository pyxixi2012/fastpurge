#include "RedisPurger.h"

RedisPurger::RedisPurger(ev::loop_ref& loop)
	: BaseAdapter(loop) {
}

void RedisPurger::purge() {
	/* Do something */
}
