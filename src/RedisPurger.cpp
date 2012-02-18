#include "RedisPurger.h"

RedisPurger::RedisPurger(ev::loop_ref& loop_, char const *address_) : BaseAdapter(loop_, address_) {
  printf("redispurger initialized: %s \n", this->address);
}

void RedisPurger::purge() {
  /* Do something */
}
