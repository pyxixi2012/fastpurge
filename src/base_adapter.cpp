class BaseAdapter {

  BaseAdapter(struct ev_loop* ev_, const std::vector<std::string>& patterns_, adapter_config* config_) : 
    ev(ev_), patterns(patterns_), config(config_) {
    printf('initialized');
  }

}