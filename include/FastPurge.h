#ifndef fastpurge_Engine_h
#define fastpurge_Engine_h (1)

namespace fastpurge {

/*! \brief base class for all supported engines.
 *
 * This class shares common properties and (virtual) methods across all engines.
 *
 * An engine is to process purges to their servers in a non-blocking way.
 *
 * \see RedisPurger
 */
class BaseEngine {
protected:
	struct ev_loop* ev_;
	std::vector<std::string> patterns_;

public:
	BaseEngine(struct ev_loop* ev, const std::vector<std::string>& patterns) :
		ev_(0),
		patterns_(patterns)
	{
	}

	virtual void setup(const char* key) = 0;
};

class RedisPurger : public BaseEngine {
public:
	RedisPurger(struct ev_loop* ev, const std::vector<std::string>& patterns) :
		BaseEngine(ev, patterns)
	{
		// setup event object, server socket and feed libev with it.
	}

	virtual void setup(const char* key);

private:
	//! I/O event callback
	void io(struct ev_loop* ev, int revents);
};

}

int sample_main() {
	struct ev_loop* ev = ev_default_loop(0);
	std::vector<std::string> patterns;
	std::list<Engine*> purgers;

	purgers.push_back(new VarnishPurger(ev, patterns));
	purgers.push_back(new RedisPurger(ev, patterns));

	ev_loop(ev, 0);

	return 0;
}
