#ifndef fastpurge_VarnishPurger_h
#define fastpurge_VarnishPurger_h

#include "fastpurge.h"
#include "BaseAdapter.h"

class VarnishPurger : public BaseAdapter {

public:
	VarnishPurger(ev::loop_ref& loop_, const char* address_);

	void setOption(char opt, char* value);
	void purge();
};

#endif