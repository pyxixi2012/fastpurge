#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>
#include <ev++.h>

#include "version.h"
#include "BaseAdapter.h"
#include "RedisPurger.h"

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

void add_adapter(std::vector<BaseAdapter*>* adapters, ev::loop_ref& ev, int type, char* address){
  adapters->push_back(new RedisPurger(ev, address));
}

static int dry_run;
static int use_regex;

int main(int argc, char* argv[]){
  std::vector<std::string> patterns;
  std::vector<BaseAdapter*> adapters;
  int c;

  ev::default_loop ev;

  while (1) {
    int option_index = 0;
    static struct option long_options[] =
    { 
      {"redis",      1, no_argument, ADAPTER_REDIS},
      {"memcached",  1, no_argument, ADAPTER_MEMCACHED},
      {"varnish",    1, no_argument, ADAPTER_VARNISH},
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

      case ADAPTER_REDIS:
        add_adapter(&adapters, ev, ADAPTER_REDIS, strdup("fnord"));
        break;

      case ADAPTER_MEMCACHED:
        printf("not yet implemented\n");
        break;

      case ADAPTER_VARNISH:
        printf("not yet implemented\n");
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

  if (optind < argc) {
    while (optind < argc)
      patterns.push_back(argv[optind++]);
  }

  if (adapters.size() == 0) {
    printf("ERROR: no adapters\n");
    printf("  --help for more information\n");
    return 1;
  }

  /* TODO: Actually do something */

  /* ev.run(); */

  return 0;
}

