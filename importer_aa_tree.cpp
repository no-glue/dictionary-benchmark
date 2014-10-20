#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "cstring_wrapper.h"
#include <queue>
#include <stack>
#include <time.h>
#include "aa_node.h"
#include "aa_tree.h"
#include "double_node.h"
#include "double_list.h"
#include "adapter_metrics_aa_tree.h"
#include "decorator_file_read.h"
#include "generator_file.h"
#include "importer.h"
#include "metrics.h"
#include "timer.h"

using namespace std;

int main() {
  string line;
  getline(cin, line);
  DoubleList<
    DoubleNode<string>,
    string
  > * results = new DoubleList<
    DoubleNode<string>,
    string
  >();
  // results
  AaTree<
    AaNode<string, vector<string> >,
    string
  > * tree = new AaTree<
    AaNode<string, vector<string> >,
    string
  >();
  // tree
  CstringWrapper * wrapper = new CstringWrapper(), * str_timer = new CstringWrapper();
  // string helper
  AdapterMetricsAaTree<
    string,
    queue<string>,
    queue<int>,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>,
    AaNode<string, vector<string> >,
    AaTree<
      AaNode<string, vector<string> >,
      string
    > 
  > * adapter = new AdapterMetricsAaTree<
    string,
    queue<string>,
    queue<int>,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>,
    AaNode<string, vector<string> >,
    AaTree<
      AaNode<string, vector<string> >,
      string
    >
  >(wrapper, results, tree);
  // metrics (use it as adapter)
  GeneratorFile<
    ifstream, string
  > * files = new GeneratorFile<
    ifstream, string
  >(line);
  // get file generator
  DecoratorFileRead<
    ostream, string
  > * file_read = new DecoratorFileRead<
    ostream, string
  >(cout);
  // get file read messages
  Importer<
    GeneratorFile<ifstream, string>, 
    AaTree<
      AaNode<string, vector<string> >,
      string
    >, 
    DecoratorFileRead<ostream, string>, 
    string, 
    ifstream
  > * importer = new Importer<
    GeneratorFile<ifstream, string>, 
    AaTree<
      AaNode<string, vector<string> >,
      string
    >, 
    DecoratorFileRead<ostream, string>, 
    string, 
    ifstream
  >();
  // importer
  Timer<
    time_t,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>
  > * timer = new Timer<
    time_t,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>
  >(str_timer);
  // timer
  Metrics<
    // start template list
    AdapterMetricsAaTree<
      string,
      queue<string>,
      queue<int>,
      CstringWrapper,
      DoubleList<DoubleNode<string>, string>,
      AaNode<string, vector<string> >,
      AaTree<
        AaNode<string, vector<string> >,
        string
      > 
    >
    // adapter for index (table here)
  > * metrics = new Metrics<
    // start template list
    AdapterMetricsAaTree<
      string,
      queue<string>,
      queue<int>,
      CstringWrapper,
      DoubleList<DoubleNode<string>, string>,
      AaNode<string, vector<string> >,
      AaTree<
        AaNode<string, vector<string> >,
        string
      > 
    >
    // adapter for index (table here)
  >(adapter);
  results->insert_right("title", "indexing(seconds)");
  results->insert_right("title", "nodes");
  results->insert_right("title", "edges");
  results->insert_right("title", "density");
  results->insert_right("title", "average degree");
  results->insert_right("title", "diameter");
  results->insert_right("title", "average path length");
  results->insert_right("title", "bfs(seconds)");
  results->insert_right("end", "end");
  timer->set_sooner(time(NULL));
  importer->import(files, tree, file_read);
  timer->set_later(time(NULL));
  timer->set_difference(difftime(timer->get_later(), timer->get_sooner()));
  timer->collect_difference(results);
  metrics->collect_nodes();
  metrics->collect_edges();
  metrics->collect_density();
  metrics->collect_average_degree();
  timer->set_sooner(time(NULL));
  metrics->breadth_first_search();
  timer->set_later(time(NULL));
  timer->set_difference(difftime(timer->get_later(), timer->get_sooner()));
  timer->collect_difference(results);
  results->insert_right("end", "end");
  while(results->get_head()) {
    cout<<results->get_head()->key<<" "<<results->get_head()->value<<endl;
    results->pop_left();
  }
  delete results;
  delete tree;
  delete adapter;
  delete files;
  delete file_read;
  delete importer;
  delete str_timer;
  delete timer;
  delete metrics;
  return 0;
}