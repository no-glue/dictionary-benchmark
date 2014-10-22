#if !defined(BUFFER_SIZE)
#define BUFFER_SIZE 128
#endif
template<typename Type, typename Stream, class Wrapper, class List>class Status {
public:
  Status() {}
  Status(Wrapper * & wrapper):wrapper(wrapper) {}
  void status(List * & results) {
    // pick up process status
    status(wrapper, key, value, buffer, results);
  }
private:
  Wrapper * wrapper;
  char * key;
  char * value;
  char buffer[BUFFER_SIZE];
  void status(Wrapper * & wrapper, char * key, char * value, char * buffer, List * & results) {
    // pick up process status
    Type line, vmpeak;
    Stream stat_stream("/proc/self/status", Stream::in);
    int i = 0;
    double temp;
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
    temp = wrapper->alpha_to_float(value) / 1024.0;
    wrapper->clear(buffer, BUFFER_SIZE);
    wrapper->float_to_alpha(buffer, temp);
    results->insert_right(key, buffer);
  }
};