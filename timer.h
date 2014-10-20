#if !defined(BUFFER_SIZE)
#define BUFFER_SIZE 128
#endif
template<typename Time, class Wrapper, class List>class Timer {
public:
  Timer():wrapper(NULL), sooner(0), later(0), difference(0) {}
  Timer(Wrapper * & wrapper):wrapper(wrapper), sooner(0), later(0), difference(0) {}
  Timer(Wrapper * & wrapper, Time sooner, Time later, Time difference):wrapper(wrapper), sooner(sooner), later(later), difference(difference) {}
  void set_sooner(Time _sooner) {sooner = _sooner;}
  Time get_sooner() {return sooner;}
  void set_later(Time _later) {later = _later;}
  Time get_later() {return later;}
  void set_difference(Time _difference) {difference = _difference;}
  void collect_difference(List * & results) {collect_difference(difference, buffer, wrapper, results);}
private:
  Wrapper * wrapper;
  char buffer[BUFFER_SIZE];
  Time sooner;
  Time later;
  Time difference;
  void collect_difference(Time difference, char * buffer, Wrapper * & wrapper, List * & results) {
    // add difference to results
    wrapper->clear(buffer, BUFFER_SIZE);
    wrapper->int_to_alpha(buffer, difference);
    results->insert_right("seconds", buffer);
  }
};