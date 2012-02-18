#ifndef fastpurge_AdapterConfig_h
#define fastpurge_AdapterConfig_h (1)

  struct adapter_config {
  	char address[4];
  	int* port;

  	char* redis_hdel;
  	char* redis_sdel;
  	char* redis_zdel;
  	int redis_rdb;
  };

#endif