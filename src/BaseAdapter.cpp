#include "BaseAdapter.h"

BaseAdapter::BaseAdapter(ev::loop_ref& loop_, const char* address_) : loop(loop_) {
	regex_t xp_addr;
	regcomp(&xp_addr, XP_ADDRESS, REG_EXTENDED);

	if(regexec(&xp_addr, address_, 0, NULL, 0) != 0){
		printf("invalid address: %s\n", address_);
		exit(1);
	} else {
		this->address = address_;
	}
}

void BaseAdapter::addPattern(std::string pattern) {
	printf("registered pattern: %s\n", pattern.c_str());
	this->string_patterns.push_back(pattern); /* <-- needs a template? */
}

void BaseAdapter::addPattern(regex_t& pattern) {
	printf("registered regex pattern\n");
	this->regex_patterns.push_back(pattern);
}
