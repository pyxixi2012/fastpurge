class BaseAdapter {

  BaseAdapter(struct ev_loop* ev_, char* address_, const std::vector<std::string>& patterns_) : 
    ev(ev_), address(address_), patterns(patterns_){
    printf('initialized');
  }

}