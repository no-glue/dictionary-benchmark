template<typename Type, typename Stream, class Wrapper, class List>class Status {
public:
  Status() {}
  Status(Wrapper * & wrapper):wrapper(wrapper) {}
  void status(List * & results) {
    // pick up process status
    status(wrapper, key, value, results);
  }
private:
  Wrapper * wrapper;
  char * key;
  char * value;
  void status(Wrapper * & wrapper, char * key, char * value, List * & results) {
    // pick up process status
    Type line, vmpeak;
    Stream stat_stream("/proc/self/status", Stream::in);
    int i = 0;
    while(getline(stat_stream, line)) if(!strncmp(line.c_str(), "VmPeak:", 7)) vmpeak = line;
    // any more stats here
    // cat /proc/$$/status for example
    stat_stream.close();
    for(; i < vmpeak.length(); i++) {
      if(vmpeak[i] == ' ' || vmpeak[i] == '\n') vmpeak.erase(i, 1);
    }
    vmpeak.erase(vmpeak.length() - 2, 2);
    key = wrapper->token(vmpeak.c_str(), ":");
    value = wrapper->token(NULL, ":");
    results->insert_right(key, value);
  }
};