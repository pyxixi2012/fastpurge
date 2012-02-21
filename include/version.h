#ifndef VERSION_H
#define VERSION_H

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1

#define VERSION_STRING "fastpurge %i.%i.%i\n\n"

#define LICENSE_STRING "Copyright © 2012\n" \
  "  Paul Asmuth <paul@paulasmuth.com>  \n" \
  "  Mikael Voss <mikael@illdefined.org>\n"

#define USAGE_STRING "usage:" \
  " %s [-xnvhs] [--redis|--varnish| SERVER]... [OPTIONS]... [PATTERN]...            \n" \
  "                                                                                 \n" \
  "  -x, --regex                                                                    \n" \
  "    use regexes instead of plain keys                                            \n" \
  "                                                                                 \n" \
  "  -d, --dry-run                                                                  \n" \
  "    print the matching keys, but do not delete                                   \n" \
  "                                                                                 \n" \
  "  -s, --silent                                                                   \n" \
  "    don't print the matching keys                                                \n" \
  "                                                                                 \n" \
  "  -v, --version                                                                  \n" \
  "    print version and exit                                                       \n" \
  "                                                                                 \n" \
  "  -h, --help                                                                     \n" \
  "    print this message and exit                                                  \n" \
  "                                                                                 \n" \
  "                                                                                 \n" \
  "Adapters:                                                                        \n" \
  "                                                                                 \n" \
  "  --redis=HOST(:PORT)                                                            \n" \
  "    purge from redis HOST (multiple allowed)                                     \n" \
  "                                                                                 \n" \
  "  --varnish=HOST(:PORT)                                                          \n" \
  "    purge from varnish HOST (multiple allowed)                                   \n" \
  "                                                                                 \n" \
  "                                                                                 \n" \
  "Redis options:                                                                   \n" \
  "                                                                                 \n" \
  "  --hdel=HASH                                                                    \n" \
  "    delete keys from hash HASH                                                   \n" \
  "                                                                                 \n" \
  "  --sdel=SET                                                                     \n" \
  "    delete keys from set SET                                                     \n" \
  "                                                                                 \n" \
  "  --zdel=SET                                                                     \n" \
  "    delete keys from sorted set SET                                              \n" \
  "                                                                                 \n" \
  "  --rdb=DB                                                                       \n" \
  "    use redis database number DB (default is zero)                               \n" \
  "\n\n"

#endif
