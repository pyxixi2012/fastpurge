#ifndef fastpurge_BaseAdapter_h
#define fastpurge_BaseAdapter_h (1)

/*! \brief base class for all supported adapters.
*
* This class shares common properties and (virtual) methods across all engines.
*
* An adapter is to process purges to their servers in a non-blocking way.
*
* \see RedisPurger
*/
class BaseAdapter {
protected:
  struct ev_loop* ev_;
  std::vector<std::string> patterns_;

public:
  BaseAdapter(struct ev_loop* ev, const std::vector<std::string>& patterns) :
    ev_(0),
    patterns_(patterns)
  {
  }

  virtual void purge(const char* keys) = 0;
};

#endif