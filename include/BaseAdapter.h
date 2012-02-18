#ifndef fastpurge_BaseAdapter_h
#define fastpurge_BaseAdapter_h

#include <string>
#include <vector>
#include <regex.h>
#include <ev++.h>

#define ADAPTER_REDIS 1
#define ADAPTER_MEMCACHED 2
#define ADAPTER_VARNISH 3

#define XP_ADDRESS "^([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})(:([0-9]{1,6}))?$"

class BaseAdapter {
protected:
  ev::loop_ref& loop;
  char const *address;
  std::vector<std::string> patterns;

  BaseAdapter(ev::loop_ref& loop_, char const *address_);

public:
  void addStringPattern(std::string);
  void setup(ev::loop_ref&);

  virtual void purge() = 0;
};

#endif
