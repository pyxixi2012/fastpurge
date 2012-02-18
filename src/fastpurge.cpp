#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ev++.h>

#include "version.h"
#include "adapter_config.h"
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
  std::vector<BaseAdapter*> adapters;
  std::vector<adapter_config*> adapter_configs;
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
        /*add_adapter(&adapter_configs, ADAPTER_REDIS, optarg);*/        
        break;

      case '2':
        /*add_adapter(&adapter_configs, ADAPTER_MEMCACHED, optarg);*/        
        break;

      case '3':
        /*add_adapter(&adapter_configs, ADAPTER_VARNISH, optarg);*/
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

  dry_run = !!dry_run;
  use_regex = !!use_regex;  
          
  if (optind < argc){
    while (optind < argc)
      patterns.push_back(argv[optind++]);      
  }

  if(adapters.size() == 0){
    printf("ERROR: no adapters\n");    
    printf("  --help for more information\n");
    return 1;
  } 

  /* initialize all adapters from adapter_configs */

  ev::default_loop eventLoop;

  /* TODO: Actually do something */

  eventLoop.run();

  return 0;
}

