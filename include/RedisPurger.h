#ifndef fastpurge_RedisPurger_h
#define fastpurge_RedisPurger_h

#include "BaseAdapter.h"

class RedisPurger : public BaseAdapter {

public:
  RedisPurger(char* address);
  void purge();
};

#endif
