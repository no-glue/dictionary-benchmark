#define BUFFER_SIZE 128
template<typename Type, class Wrapper, class Node, class List, class Walk, class Table, class TableVisited>class AdapterMetricsTable {
public:
  AdapterMetricsTable() {}
  AdapterMetricsTable(Wrapper * & wrapper, Table * & table, TableVisited * & table_visited, List * & results):
    wrapper(wrapper), table(table), table_visited(table_visited), results(results) {}
  void collect_dataset() {insert_results("dataset", table, results);}
  void collect_size() {insert_results("dataset(mb)", table, results);}
  void collect_density() {
    // add density to results
    collect_density(wrapper, buffer, results);
  }
  double density() {
    // density
    return density((double) edges(), (double) nodes());
  }
  void collect_average_degree() {
    // add average degree to results
    collect_average_degree(wrapper, buffer, results);
  }
  double average_degree() {
    // average degree
    return average_degree((double) edges(), (double) nodes());
  }
  void collect_nodes() {
    // add number of nodes to results
    insert_results("nodes", table, results);
  }
  int nodes() {
    // number of nodes
    return find_single_int("nodes", table);
  }
  void collect_edges() {
    // add number of edges to results
    insert_results("edges", table, results);
  }
  int edges() {
    // number of edges
    return find_single_int("edges", table);
  }
  void breadth_first_search() {
    breadth_first_search(wrapper, table, table_visited, buffer, results);
  }
  int find_single_int(Type key) {
    // find single item of type int
    return find_single_int(key, table);
  }
private:
  Wrapper * wrapper;
  Table * table;
  TableVisited * table_visited;
  List * results;
  char buffer[BUFFER_SIZE];
  void collect_density(Wrapper * & wrapper, char * buffer, List * & results) {
    // add density to results
    wrapper->clear(buffer, BUFFER_SIZE);
    double e = (double) find_single_int("edges");
    double n = (double) find_single_int("nodes");
    wrapper->float_to_alpha(buffer, density(e, n));
    results->insert_right("density", buffer);
  }
  double density(double edges, double nodes) {
    // density
   return (2 * edges) / (nodes * (nodes - 1)); 
  }
  void collect_average_degree(Wrapper * & wrapper, char * buffer, List * & results) {
    // add density to results
    wrapper->clear(buffer, BUFFER_SIZE);
    double e = (double) find_single_int("edges");
    double n = (double) find_single_int("nodes");
    wrapper->float_to_alpha(buffer, average_degree(e, n));
    results->insert_right("average degree", buffer);
  }
  double average_degree(double edges, double nodes) {
    // average degree
    return (2 * edges) / nodes;
  }
  void insert_results(Type key, Table * & table, List * & results) {
    // insert to results
    table->find(key, results);
  }
  int find_single_int(Type key, Table * & table) {
    // find single item of type int
    List * result = new List();
    table->find(key, result);
    int item = atoi(result->get_head()->value);
    delete result;
    return item;
  }
  void breadth_first_search(Wrapper * & wrapper, Table * & table, TableVisited * & table_visited, char * buffer, List * & results) {
    Node * current;
    Node * current_running;
    Walk * walk = new Walk();
    List * running = new List();
      table->find("startnode", running);
    List * depth = new List();
    double paths = 0;
    double lengths = 0;
    double average_path_length = 0;
    List * node = new List();
      table->find(running->get_head()->value, node);
      running->make_empty();
      walk->set_list(node);
      walk->rewind();
      table_visited->insert_unique(node->get_head()->key, node->get_head()->key);
      while((current = walk->next())) {
        paths++;
        lengths++;
        average_path_length = lengths / paths;
        depth->insert_right("1", "1");
        table_visited->insert_unique(current->value, current->value);
      }
      walk->unset_list();
    int diameter = 0;
    while(node->get_head()) {
        table->find(node->get_head()->value, running);
        while((current_running = running->get_head())) {
          if(table_visited->insert_unique(current_running->value, current_running->value)) {
            paths++;
            lengths += atoi(depth->get_head()->value);
            average_path_length = lengths / paths;
            node->insert_right(current_running->value, current_running->value);
            diameter = atoi(depth->get_head()->value) + 1;
            wrapper->clear(buffer, BUFFER_SIZE);
            wrapper->int_to_alpha(buffer, diameter);
            depth->insert_right(buffer, buffer);
          }
          running->pop_left();
        }
      node->pop_left();
      depth->pop_left();
    }
    results->insert_right("network diameter", buffer);
    wrapper->clear(buffer, BUFFER_SIZE);
    wrapper->float_to_alpha(buffer, average_path_length);
    results->insert_right("average path length", buffer);
    delete walk;
    delete running;
    delete depth;
    delete node;
  }
};