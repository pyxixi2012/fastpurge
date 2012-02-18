#ifndef fastpurge_BaseAdapter_h
#define fastpurge_BaseAdapter_h (1)

/*! \brief base class for all supported adapters.
*
* This class shares common properties and (virtual) methods across all engines.
* An adapter is to process purges to their servers in a non-blocking way.
*
* \see RedisPurger
*/
class BaseAdapter {
protected:
  struct ev_loop* ev;
  char* address;
  std::vector<std::string> patterns;  

public:
  BaseAdapter(struct ev_loop* ev_, char* address_, const std::vector<std::string>& patterns_);

  /*virtual void purge(const char* keys) = 0;*/
};

#endif