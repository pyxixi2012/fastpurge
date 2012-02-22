#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>
#include <ev++.h>

#include "version.h"
#include "fastpurge.h"
#include "BaseAdapter.h"
#include "RedisPurger.h"
#include "VarnishPurger.h"

/*
	FIXPAUL: TODO: fastpurged (daemonize and listen on redis for patterns)
	FIXPAUL: TODO: detect stub patterns like /^fnord$/ and use simple key delete
	FIXPAUL: --dry-run is working, but -d is not  
	FIXPAUL: Y U NO TERMINATE?
	FIXPAUL: segfault on connection refused
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

int dry_run = 0;
int use_regex = 0;
int silent = 0;

int main(int argc, char* argv[]) {
	std::vector<std::string> patterns;
	std::vector<BaseAdapter*> adapters;

	ev::default_loop ev;

	while (1) {
		int option_index = 0;
		static struct option long_options[] = { 
			{ "redis",     required_argument, nullptr,    ADAPTER_REDIS },
			{ "varnish",   required_argument, nullptr,    ADAPTER_VARNISH },
			{ "hdel",      required_argument, nullptr,    OPT_HDEL },
			{ "zdel",      required_argument, nullptr,    OPT_ZDEL },
			{ "sdel",      required_argument, nullptr,    OPT_SDEL },
			{ "rdb",       required_argument, nullptr,    OPT_RDB  },
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

			case ADAPTER_VARNISH:
				adapters.push_back(new VarnishPurger(ev, optarg));
				break;

			case OPT_HDEL:			
				for (const auto& adapter: adapters)
					adapter->setOption(OPT_HDEL, optarg);
				break;

			case OPT_SDEL:			
				for (const auto& adapter: adapters)
					adapter->setOption(OPT_SDEL, optarg);
				break;

			case OPT_ZDEL:			
				for (const auto& adapter: adapters)
					adapter->setOption(OPT_ZDEL, optarg);
				break;

			case OPT_RDB:			
				for (const auto& adapter: adapters)
					adapter->setOption(OPT_RDB, optarg);
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

	for (const auto& pattern: patterns) {
		regex_t xp_pattern;

		if (use_regex) {
			if(regcomp(&xp_pattern, pattern.c_str(), REG_EXTENDED) != 0){
				printf("invalid regex: %s\n", pattern.c_str());
				exit(1);
			}
		}

		for(std::vector<int>::size_type i = 0; i != adapters.size(); i++) {
			if (use_regex){
				adapters[i]->addPattern(xp_pattern);
			} else {
				adapters[i]->addPattern(pattern);
			}
		}
	}

	/* yay! :) */
	for (const auto& adapter: adapters) {
		adapter->purge();
	}
	
	ev_loop(ev, 0);

	return 0;
}

