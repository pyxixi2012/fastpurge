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
	this->string_patterns.push_back(pattern);
}

void BaseAdapter::addPattern(regex_t& pattern) {
	this->regex_patterns.push_back(pattern);
}

ip_addr* BaseAdapter::parseAddress(const char* address_) {
	std::string address = address_;
	ip_addr* addr = (ip_addr *)malloc(sizeof(ip_addr));
	int ind = address.find(":");

	if(ind == -1){
		addr->port = 0;	
		strncpy(addr->host, address.c_str(), sizeof(addr->host));		
	} else {
		addr->port = atoi(address.substr(ind+1).c_str());		
		strncpy(addr->host, address.substr(0, ind).c_str(), sizeof(addr->host));		
	}

	return addr;
}