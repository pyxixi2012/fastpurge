#ifndef fastpurge_BaseAdapter_h
#define fastpurge_BaseAdapter_h

#include <string>
#include <vector>

#include <ev++.h>

#define ADAPTER_REDIS 1
#define ADAPTER_MEMCACHED 2
#define ADAPTER_VARNISH 3

class BaseAdapter {
protected:
  /*struct ev::loop_ref& loop;*/
  std::vector<std::string> patterns;

  BaseAdapter(char* address);

public:
  void setPatterns(std::vector<std::string> const&);
  void setup(ev::loop_ref&);

  virtual void purge() = 0;
};

#endif
