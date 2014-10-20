#if !defined(BUFFER_SIZE)
#define BUFFER_SIZE 128
#endif
template<typename Stream, typename Type, class Wrapper, class Node, class List>class Writer {
public:
  Writer() {}
  Writer(Wrapper * & wrapper):wrapper(wrapper) {}
  void write(Type index, List * & results) {
    // write results to file
    write(wrapper, buffer, index, results);
  }
private:
  Wrapper * wrapper;
  char buffer[BUFFER_SIZE];
  void write(Wrapper * & wrapper, char * buffer, Type index, List * & results) {
    // write results to file
    Node * node = results->get_head();
    wrapper->clear(buffer, BUFFER_SIZE);
    wrapper->copy(buffer, "results_");
    wrapper->concat(buffer, index.c_str());
    wrapper->concat(buffer, "_");
    wrapper->concat(buffer, node->value);
    Stream out(buffer, Stream::out);
    results->pop_left();
    while((node = results->get_head())) {
      out<<node->key<<"\t"<<node->value<<"\n";
      results->pop_left();
    }
    out.close();
  }
};