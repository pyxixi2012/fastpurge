#include "RedisPurger.h"

RedisPurger::RedisPurger(char* address) : BaseAdapter(address) {
  printf("redispurger initialized: %s \n", address);
}

void RedisPurger::purge() {
  /* Do something */
}
