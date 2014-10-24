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
#include "writer.h"
#include "status.h"

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
  CstringWrapper * wrapper = new CstringWrapper(), * str_timer = new CstringWrapper(), * str_writer = new CstringWrapper(), * str_status = new CstringWrapper();
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
    string,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>
  > * timer = new Timer<
    time_t,
    string,
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
  // metrics
  Writer<
    ofstream,
    string,
    CstringWrapper,
    DoubleNode<string>,
    DoubleList<DoubleNode<string>, string>
  > * writer = new Writer<
    ofstream,
    string,
    CstringWrapper,
    DoubleNode<string>,
    DoubleList<DoubleNode<string>, string>
  >(str_writer);
  // writer
  Status<
    string,
    ifstream,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>
  > * status = new Status<
    string,
    ifstream,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>
  >(str_status);
  // process status
  timer->set_sooner(time(NULL));
  importer->import(files, tree, file_read);
  timer->set_later(time(NULL));
  timer->set_difference(difftime(timer->get_later(), timer->get_sooner()));
  metrics->collect_dataset();
  metrics->collect_size();
  status->status(results);
  timer->collect_difference("indexing(sec)", results);
  timer->set_sooner(time(NULL));
  metrics->breadth_first_search();
  timer->set_later(time(NULL));
  timer->set_difference(difftime(timer->get_later(), timer->get_sooner()));
  timer->collect_difference("bfs(sec)", results);
  metrics->collect_nodes();
  metrics->collect_edges();
  metrics->collect_density();
  metrics->collect_average_degree();
  metrics->collect_specific_metric();
  writer->write("aa_tree", results);
  delete results;
  delete tree;
  delete adapter;
  delete files;
  delete file_read;
  delete importer;
  delete str_timer;
  delete timer;
  delete metrics;
  delete str_writer;
  delete writer;
  delete str_status;
  delete status;
  return 0;
}