#define SIZE 4294967295

#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "cstring_wrapper.h"
#include "double_node.h"
#include "double_list.h"
#include "double_list_walk.h"
#include "hash_djb2_string.h"
#include "chained_hash_table.h"
#include "decorator_file_read.h"
#include "generator_file.h"
#include "importer.h"
#include "adapter_metrics_table.h"
#include "metrics.h"
#include "timer.h"

using namespace std;

int main() {
  string line;
  getline(cin, line);
  CstringWrapper * str = new CstringWrapper(), * str_timer = new CstringWrapper();
  // get str
  DoubleList<DoubleNode<string>, string> * results = new DoubleList<DoubleNode<string>, string>;
  // get results
  DoubleListWalk<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>
  > * table_walk = new DoubleListWalk<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>
  >(), 
  * table_visited_walk = new DoubleListWalk<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>
  >();
  // get walks
  HashDjb2String<
    string
  > * hash = new HashDjb2String<
    string
  >(), 
  * hash_table_visited = new HashDjb2String<
    string
  >();
  // get hashes
  ChainedHashTable<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>, 
    HashDjb2String<string>,
    DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
    string
  > * table = new ChainedHashTable<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>, 
    HashDjb2String<string>,
    DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
    string
  >(ceil(SIZE / sizeof(DoubleNode<string>)), table_walk, hash),
  * table_visited = new ChainedHashTable<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>, 
    HashDjb2String<string>,
    DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
    string
  >(ceil(SIZE / sizeof(DoubleNode<string>)), table_visited_walk, hash_table_visited);
  // get tables
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
    ChainedHashTable<
      DoubleNode<string>, 
      DoubleList<DoubleNode<string>, string>, 
      HashDjb2String<string>,
      DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
      string>, 
    DecoratorFileRead<ostream, string>, 
    string, 
    ifstream> * importer = new Importer<
      GeneratorFile<ifstream, string>, 
      ChainedHashTable<
        DoubleNode<string>, 
        DoubleList<DoubleNode<string>, string>, 
        HashDjb2String<string>,
        DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
        string>, 
      DecoratorFileRead<ostream, string>, 
      string, 
      ifstream>();
  // get file reader
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
  AdapterMetricsTable<
    string,
    // keys and values simple type
    CstringWrapper,
    // wrapper to use for strings
    DoubleNode<string>,
    // node
    DoubleList<DoubleNode<string>, string>,
    // list
    DoubleListWalk<
      DoubleNode<string>,
      DoubleList<DoubleNode<string>, string>
    >,
    // walk list
    ChainedHashTable<
      DoubleNode<string>, 
      DoubleList<DoubleNode<string>, string>, 
      HashDjb2String<string>,
      DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
      string
    >,
    ChainedHashTable<
      DoubleNode<string>, 
      DoubleList<DoubleNode<string>, string>, 
      HashDjb2String<string>,
      DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
      string
    >
    // table 
  > * adapter = new AdapterMetricsTable<
    string,
    // keys and values simple type
    CstringWrapper,
    // wrapper to use for strings
    DoubleNode<string>,
    // node
    DoubleList<DoubleNode<string>, string>,
    // list
    DoubleListWalk<
      DoubleNode<string>,
      DoubleList<DoubleNode<string>, string>
    >,
    // walk list
    ChainedHashTable<
      DoubleNode<string>, 
      DoubleList<DoubleNode<string>, string>, 
      HashDjb2String<string>,
      DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
      string
    >,
    ChainedHashTable<
      DoubleNode<string>, 
      DoubleList<DoubleNode<string>, string>, 
      HashDjb2String<string>,
      DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
      string
    >
    // table
  >(str, table, table_visited, results);
  // get table adapter
  // todo put walk in front
  Metrics<
    // start template list
    AdapterMetricsTable<
      string,
      // keys and values simple type
      CstringWrapper,
      // wrapper to use for strings
      DoubleNode<string>,
      // node
      DoubleList<DoubleNode<string>, string>,
      // list
      DoubleListWalk<
        DoubleNode<string>,
        DoubleList<DoubleNode<string>, string>
      >,
      // walk list
      ChainedHashTable<
        DoubleNode<string>, 
        DoubleList<DoubleNode<string>, string>, 
        HashDjb2String<string>,
        DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
        string
      >,
      ChainedHashTable<
        DoubleNode<string>, 
        DoubleList<DoubleNode<string>, string>, 
        HashDjb2String<string>,
        DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
        string
      >
      // table 
    >
    // adapter for index (table here)
  > * metrics = new Metrics<
    // start template list
    AdapterMetricsTable<
      string,
      // keys and values simple type
      CstringWrapper,
      // wrapper to use for strings
      DoubleNode<string>,
      // node
      DoubleList<DoubleNode<string>, string>,
      // list
      DoubleListWalk<
        DoubleNode<string>,
        DoubleList<DoubleNode<string>, string>
      >,
      // walk list
      ChainedHashTable<
        DoubleNode<string>, 
        DoubleList<DoubleNode<string>, string>, 
        HashDjb2String<string>,
        DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
        string
      >,
      ChainedHashTable<
        DoubleNode<string>, 
        DoubleList<DoubleNode<string>, string>, 
        HashDjb2String<string>,
        DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
        string
      >
      // table 
    >
    // adapter for index (table here)
  >(adapter);
  // get metrics
  // todo make single metrics
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
  importer->import(files, table, file_read);
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
  delete str;
  delete results;
  delete table_walk;
  delete table_visited_walk;
  delete hash;
  delete hash_table_visited;
  delete table;
  delete table_visited;
  delete files;
  delete file_read;
  delete str_timer;
  delete timer;
  delete importer;
  delete adapter;
  delete metrics;
  return 0;
}