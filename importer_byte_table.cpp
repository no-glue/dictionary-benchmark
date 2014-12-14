#define SIZE 131072
#define ARRAY_SIZE 131072
// todo ... switch ... on load, 80% switch table

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <time.h>
#include <math.h>
#include "byte_array.h"
#include "byte_table.h"
#include "filter.h"
#include "byte_table_as_list.h"
#include "tokenizer.h"
#include "cstring_wrapper.h"
#include "double_node.h"
#include "double_list.h"
#include "hash_djb2_string.h"
#include "double_list_walk.h"
#include "decorator_file_read.h"
#include "generator_file.h"
#include "importer.h"
#include "adapter_metrics_table.h"
#include "metrics.h"
#include "timer.h"
#include "writer.h"
#include "status.h"

using namespace std;

int main() {
  string line;
  getline(cin, line);
  CstringWrapper * str = new CstringWrapper(), * str_timer = new CstringWrapper(), * str_adapter = new CstringWrapper();
  // str for c strings
  HashDjb2String<string> * hash = new HashDjb2String<string>(), * hash_visited = new HashDjb2String<string>();
  // hash
  DoubleList<
    DoubleNode<string>, 
    string
  > * results = new DoubleList<
    DoubleNode<string>, 
    string
  >();
  // results
  ByteTable<
    ByteArray,
    HashDjb2String<string>
  > * table_base = new ByteTable<
    ByteArray,
    HashDjb2String<string>
  >(SIZE, ARRAY_SIZE, hash);
  // table base
  ByteTableAsList<
    string,
    DoubleList<DoubleNode<string>, string >,
    ByteArray,
    ByteTable<ByteArray, HashDjb2String<string> >
  > * table = new ByteTableAsList<
    string,
    DoubleList<DoubleNode<string>, string >,
    ByteArray,
    ByteTable<ByteArray, HashDjb2String<string> >
  >(table_base);
  // table
  ByteTable<
    ByteArray,
    HashDjb2String<string>
  > * table_base_visited = new ByteTable<
    ByteArray,
    HashDjb2String<string>
  >(SIZE, ARRAY_SIZE, hash_visited);
  // tabe base visited
  ByteTableAsList<
    string,
    DoubleList<DoubleNode<string>, string >,
    ByteArray,
    ByteTable<ByteArray, HashDjb2String<string> >
  > * table_visited = new ByteTableAsList<
    string,
    DoubleList<DoubleNode<string>, string >,
    ByteArray,
    ByteTable<ByteArray, HashDjb2String<string> >
  >(table_base_visited);
  // tabe visited
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
    ByteTableAsList<
      string,
      DoubleList<DoubleNode<string>, string >,
      ByteArray,
      ByteTable<ByteArray, HashDjb2String<string> >
    >,
    DecoratorFileRead<ostream, string>, 
    string, 
    ifstream> * importer = new Importer<
      GeneratorFile<ifstream, string>, 
      ByteTableAsList<
        string,
        DoubleList<DoubleNode<string>, string >,
        ByteArray,
        ByteTable<ByteArray, HashDjb2String<string> >
      >,
      DecoratorFileRead<ostream, string>, 
      string, 
      ifstream>();
  // get file reader
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
    ByteTableAsList<
      string,
      DoubleList<DoubleNode<string>, string >,
      ByteArray,
      ByteTable<ByteArray, HashDjb2String<string> >
    >,
    ByteTableAsList<
      string,
      DoubleList<DoubleNode<string>, string >,
      ByteArray,
      ByteTable<ByteArray, HashDjb2String<string> >
    >
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
    ByteTableAsList<
      string,
      DoubleList<DoubleNode<string>, string >,
      ByteArray,
      ByteTable<ByteArray, HashDjb2String<string> >
    >,
    ByteTableAsList<
      string,
      DoubleList<DoubleNode<string>, string >,
      ByteArray,
      ByteTable<ByteArray, HashDjb2String<string> >
    >
    // table
  >(str_adapter, table, table_visited, results);
  // adapter
  Metrics<
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
      ByteTableAsList<
       string,
       DoubleList<DoubleNode<string>, string >,
       ByteArray,
       ByteTable<ByteArray, HashDjb2String<string> >
      >,
      ByteTableAsList<
       string,
       DoubleList<DoubleNode<string>, string >,
       ByteArray,
       ByteTable<ByteArray, HashDjb2String<string> >
      >
    >
  > * metrics = new Metrics<
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
      ByteTableAsList<
       string,
       DoubleList<DoubleNode<string>, string >,
       ByteArray,
       ByteTable<ByteArray, HashDjb2String<string> >
      >,
      ByteTableAsList<
       string,
       DoubleList<DoubleNode<string>, string >,
       ByteArray,
       ByteTable<ByteArray, HashDjb2String<string> >
      >
    >
  >(adapter);
  // metrics
  timer->set_sooner(time(NULL));
  importer->import(files, table, file_read);
  timer->set_later(time(NULL));
  timer->set_difference(difftime(timer->get_later(), timer->get_sooner()));
  metrics->collect_dataset();
  metrics->collect_size();
  metrics->collect_nodes();
  metrics->collect_edges();
  metrics->collect_density();
  metrics->collect_average_degree();
  while(results->get_head()) {
    cout<<results->get_head()->key<<" "<<results->get_head()->value<<endl;
    results->pop_left();
  }
  delete str;
  delete str_timer;
  delete str_adapter;
  delete hash;
  delete hash_visited;
  delete results;
  delete table_base;
  delete table_base_visited;
  delete table;
  delete table_visited;
  delete files;
  delete file_read;
  delete importer;
  delete timer;
  delete adapter;
  delete metrics;
  return 0;
}
