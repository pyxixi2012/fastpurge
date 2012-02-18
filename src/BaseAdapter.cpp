#include "BaseAdapter.h"

BaseAdapter::BaseAdapter(char* address){
}

void BaseAdapter::setPatterns(std::vector<std::string> const& patterns_) {
  this->patterns = patterns_;
}
