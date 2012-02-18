#ifndef fastpurge_AdapterConfig_h
#define fastpurge_AdapterConfig_h (1)

#define ADAPTER_REDIS 1
#define ADAPTER_MEMCACHED 2
#define ADAPTER_VARNISH 3

/*
struct adapter_config {
  char adapter; 
  char address[4];
  int port;

  char* redis_hdel;
  char* redis_sdel;
  char* redis_zdel;
  int redis_rdb;
};
*/

#endif