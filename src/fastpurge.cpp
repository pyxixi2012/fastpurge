#include<stdio.h>
#include <cstdlib>
#include<vector>
#include<string>

#include <ev++.h>

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

  ev::default_loop eventLoop;

  /* TODO: Actually do something */

  eventLoop.run();

  return EXIT_SUCCESS;
}
