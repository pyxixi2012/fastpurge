#include "BaseAdapter.h"

BaseAdapter::BaseAdapter(ev::loop_ref& loop)
	: loop(loop) {
}

void BaseAdapter::setPatterns(std::vector<std::string> const& patterns) {
	/* This is one of the reasons why some people suffix
	 * member variables with underscores */
	this->patterns = patterns;
}
