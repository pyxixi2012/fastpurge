#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ev++.h>

#include "version.h"
#include "BaseAdapter.h"

/*
  FIXPAUL: --dry-run is working, but -d is not
*/

void usage(char* binary){
  printf(
    VERSION_STRING, 
    VERSION_MAJOR, 
    VERSION_MINOR, 
    VERSION_PATCH
  );
  printf(
    USAGE_STRING, 
    binary
  );
}

void version(){
  printf(
    VERSION_STRING, 
    VERSION_MAJOR, 
    VERSION_MINOR, 
    VERSION_PATCH
  );
  printf(LICENSE_STRING);
}

static int dry_run;
static int use_regex;

int main(int argc, char* argv[]){
  std::vector<std::string> patterns;
  std::vector<BaseAdapter*> purgers;
  int c;
  
  while (1) {
    int option_index = 0;
    static struct option long_options[] =
    { 
      {"redis",      1, no_argument, '1'},            
      {"memcached",  1, no_argument, '2'},
      {"varnish",    1, no_argument, '3'},
      {"help",       0, no_argument, 'h'},
      {"version",    0, no_argument, 'v'},
      {"dry-run",    0, &dry_run,    'd'},
      {"regex",      0, &use_regex,  'x'},
      {0, 0, 0, 0}
    };
          
    c = getopt_long (argc, argv, "abc:d:f:", long_options, &option_index);

    if (c == -1)
      break;
     
    switch (c) {

      case '1':
        printf("adapter -> redis: %s\n", optarg);
        break;

      case '2':
        printf("adapter -> memcached: %s\n", optarg);
        break;

      case '3':
        printf("adapter -> varnish: %s\n", optarg);
        break;

      case 'v':
        version();
        exit(0);

      case 'h':
        usage(argv[0]);
        exit(0);

      default:       
        break;

    }
  }

  printf("dry-run: %i, use-regex: %i\n", !!dry_run, !!use_regex);
          
  if (optind < argc){
    while (optind < argc)
      printf ("pattern: %s \n", argv[optind++]);
  }

  /*
    purgers.push_back(new VarnishPurger(ev, patterns));
    purgers.push_back(new RedisPurger(ev, patterns));
  */ 
  
  struct ev_loop* ev = ev_default_loop(0);

  /* TODO: Actually do something */

  ev_loop(ev, 0);
  

  return EXIT_SUCCESS;
}
