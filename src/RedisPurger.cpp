#include "fastpurge.h"
#include "RedisPurger.h"

RedisPurger::RedisPurger(ev::loop_ref& loop_, char const *address_) : BaseAdapter(loop_, address_) {
	printf("redispurger initialized: %s -> %i \n", this->address, dry_run);
}

void RedisPurger::purge() {
	printf("let's go!");
	/* Do something */
}
