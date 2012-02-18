class BaseAdapter {
protected:
  struct ev_loop* ev;
  char* address;
  std::vector<std::string> patterns;

public:
  BaseAdapter(struct ev_loop* ev_, char* address_) : ev(ev_), address(address_){
    printf("initialized");
  }

  void add_pattern(const std::vector<std::string>& patterns_){
  	/* store patterns in patterns member var */
  }

};
