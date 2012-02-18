#include "BaseAdapter.h"

BaseAdapter::BaseAdapter(ev::loop_ref& loop_, char* address_) : loop(loop_) {
  this->address = address_;
}

void BaseAdapter::setPatterns(std::vector<std::string> const& patterns_) {
  this->patterns = patterns_;
}
