#ifndef fastpurge_BaseAdapter_h
#define fastpurge_BaseAdapter_h (1)

#include <string>
#include <vector>

#include <ev++.h>

/*! \brief base class for all supported adapters.
*
* This class shares common properties and (virtual) methods across all engines.
* An adapter is to process purges to their servers in a non-blocking way.
*
* \see RedisPurger
*/
class BaseAdapter {
protected:
  struct ev::loop_ref& loop;
  std::vector<std::string> patterns;

  BaseAdapter(ev::loop_ref&);

public:
  virtual void purge(const char* keys) = 0;
};

#endif
