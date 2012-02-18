#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ev++.h>

#include "version.h"
#include "BaseAdapter.h"

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

int main(int argc, char* argv[]){
  int c;
  
  while (1) {
    int option_index = 0;
    static struct option long_options[] =
    {             
      {"help",        no_argument,       0, 'h'},
      {"version",     no_argument,       0, 'v'},
      {0, 0, 0, 0}
    };
          
    c = getopt_long (argc, argv, "abc:d:f:", long_options, &option_index);

    if (c == -1)
      break;
     
    switch (c) {

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
          
  if (optind < argc){
    while (optind < argc)
      printf ("%s \n", argv[optind++]);
  }

  printf("fnord!\n");

  /*
    
    std::vector<std::string> patterns;
    std::list<Engine*> purgers;

    purgers.push_back(new VarnishPurger(ev, patterns));
    purgers.push_back(new RedisPurger(ev, patterns));

   
  */ 
  
  struct ev_loop* ev = ev_default_loop(0);

  /* TODO: Actually do something */

  ev_loop(ev, 0);
  

  return EXIT_SUCCESS;
}
