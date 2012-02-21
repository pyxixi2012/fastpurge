#include "fastpurge.h"
#include "VarnishPurger.h"


VarnishPurger::VarnishPurger(ev::loop_ref& loop_, char const *address_) : BaseAdapter(loop_, address_) {
	printf("ERROR: varnish purger isn't implemented yet, bitch ;)\n");
	exit(1);
}

void VarnishPurger::setOption(char opt, char* value){	
	/* fnord */
}

void VarnishPurger::purge(){
	/* fnord */
}

