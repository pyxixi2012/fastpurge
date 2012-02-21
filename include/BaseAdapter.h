#ifndef fastpurge_BaseAdapter_h
#define fastpurge_BaseAdapter_h

#include <string>
#include <string.h>
#include <vector>
#include <regex.h>
#include <ev++.h>

#include "ip_addr.h"

#define ADAPTER_REDIS 'R'
#define ADAPTER_VARNISH 'V'

#define XP_ADDRESS "^([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})(:([0-9]{1,6}))?$"

class BaseAdapter {
protected:
	ev::loop_ref& loop;
	char const *address;
	std::vector<std::string> string_patterns;
	std::vector<regex_t> regex_patterns;

	BaseAdapter(ev::loop_ref& loop_, char const *address_);
	ip_addr* parseAddress(const char* address);

public:	
	void addPattern(std::string);
	void addPattern(regex_t&);  
	void setup(ev::loop_ref&);

	virtual void setOption(char opt, char* value) = 0;
	virtual void purge() = 0;
};

#endif

