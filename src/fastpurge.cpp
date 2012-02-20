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
  FIXPAUL: put options in to "bitfields-char" and pass to purgers (dry-run, regex, etc)  
*/

void usage(const char* binary) {
  printf(USAGE_STRING, binary);
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

static int dry_run = 0;
static int use_regex = 0;
static int silent = 0;

int main(int argc, char* argv[]) {
  std::vector<std::string> patterns;
  std::vector<BaseAdapter*> adapters;

  ev::default_loop ev;

  while (1) {
    int option_index = 0;
    static struct option long_options[] = { 
      { "redis",     required_argument, nullptr,    ADAPTER_REDIS },
      { "memcached", required_argument, nullptr,    ADAPTER_MEMCACHED },
      { "varnish",   required_argument, nullptr,    ADAPTER_VARNISH },
      { "regex",     no_argument,       &use_regex, 'x' },
      { "help",      no_argument,       nullptr,    'h' },
      { "version",   no_argument,       nullptr,    'v' },
      { "dry-run",   no_argument,       &dry_run,   'd' },
      { "silent",    no_argument,       &silent,    's' },
      { 0, 0, 0, 0 }
    };

    int c = getopt_long (argc, argv, "R:M:V:xhvds", long_options, &option_index);

    if (c < 0)
      break;

    switch (c) {

      case ADAPTER_REDIS:
        adapters.push_back(new RedisPurger(ev, optarg));
        break;

      case ADAPTER_MEMCACHED:
        printf("not yet implemented\n");
        break;

      case ADAPTER_VARNISH:
        printf("not yet implemented\n");
        break;

      case 'v':
        version();
        return 0;

      case 'h':
        usage(argv[0]);
        return 0;

      default:
        break;

    }
  }

  dry_run = !!dry_run;
  use_regex = !!use_regex;
  silent = !!silent;

  if (dry_run && !silent) {
    printf("Dry run enabled.\n");
  }

  if (optind < argc) {
    while (optind < argc)
      patterns.push_back(argv[optind++]);
  }

  if (adapters.size() == 0) {
    printf("ERROR: no adapters\n");
    printf("  --help for more information\n");
    return 1;
  }

  if (patterns.size() == 0) {
    printf("ERROR: no patterns/keys\n");
    printf("  --help for more information\n");
    return 1;
  }

  for(std::vector<int>::size_type j = 0; j != patterns.size(); j++) {

    regex_t xp_pattern;

    if (use_regex) {
      if(regcomp(&xp_pattern, patterns[j].c_str(), REG_EXTENDED) != 0){
        printf("invalid regex: %s\n", patterns[j].c_str());
        exit(1);
      }
    }

    for(std::vector<int>::size_type i = 0; i != adapters.size(); i++) {
      if (use_regex){
        adapters[i]->addPattern(xp_pattern);
      } else {
        adapters[i]->addPattern(patterns[j]);
      }
    }
  }

  /* ev.run(); */

  return 0;
}

// vim:ts=2:sw=2:et
