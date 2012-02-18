#include<stdio.h>
#include<vector>
#include<string>

#include "version.h"
#include "BaseAdapter.h"

int main(int argc, char* argv[]){
  printf("fnord");

  /*
	struct ev_loop* ev = ev_default_loop(0);
	std::vector<std::string> patterns;
	std::list<Engine*> purgers;

	purgers.push_back(new VarnishPurger(ev, patterns));
	purgers.push_back(new RedisPurger(ev, patterns));

	ev_loop(ev, 0);
  */ 

  return 0;
}
