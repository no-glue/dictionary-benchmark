#define SIZE 4294967295

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <time.h>
#include <math.h>
#include "unqlite_wrapper.h"
#include "tokenizer.h"
#include "cstring_wrapper.h"
#include "double_node.h"
#include "double_list.h"
#include "hash_djb2_string.h"
#include "double_list_walk.h"
#include "chained_hash_table.h"
#include "tokenizer_list.h"
#include "helper_wrapper.h"
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
  DoubleList<DoubleNode<string>, string> * results = new DoubleList<DoubleNode<string>, string>();
  Tokenizer * tokenizer = new Tokenizer();
  // tokenizer
  CstringWrapper * str = new CstringWrapper(), * str_adapter = new CstringWrapper(), * str_timer = new CstringWrapper();
  // str for c strings
  TokenizerList<
    string,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>,
    Tokenizer
  > * tokenizer_list = new TokenizerList<
    string,
    CstringWrapper,
    DoubleList<DoubleNode<string>, string>,
    Tokenizer
  >(str, tokenizer);
  // tokenizer to work with list or something else
  UnqliteWrapper<string> * table_base = new UnqliteWrapper<string>();
  // table for storing things
  DoubleListWalk<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>
  > * table_visited_walk = new DoubleListWalk<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>
  >();
  // get walks
  HashDjb2String<
    string
  > * hash_table_visited = new HashDjb2String<
    string
  >();
  // get hashes
  HelperWrapper<
    string,
    DoubleList<DoubleNode<string>, string>,
    Tokenizer,
    TokenizerList<
      string,
      CstringWrapper,
      DoubleList<DoubleNode<string>, string>,
      Tokenizer
    >,
    UnqliteWrapper<string>
  > * table = new HelperWrapper<
    string,
    DoubleList<DoubleNode<string>, string>,
    Tokenizer,
    TokenizerList<
      string,
      CstringWrapper,
      DoubleList<DoubleNode<string>, string>,
      Tokenizer
    >,
    UnqliteWrapper<string>
  >(tokenizer, tokenizer_list, table_base);
  // wrapped table
  ChainedHashTable<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>, 
    HashDjb2String<string>,
    DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
    string
  > * table_visited = new ChainedHashTable<
    DoubleNode<string>, 
    DoubleList<DoubleNode<string>, string>, 
    HashDjb2String<string>,
    DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
    string
  >(ceil(SIZE / sizeof(DoubleNode<string>)), table_visited_walk, hash_table_visited);
  // table to keep visited nodes
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
    HelperWrapper<
      string,
      DoubleList<DoubleNode<string>, string>,
      Tokenizer,
      TokenizerList<
        string,
        CstringWrapper,
        DoubleList<DoubleNode<string>, string>,
        Tokenizer
      >,
      UnqliteWrapper<string>
    >, 
    DecoratorFileRead<ostream, string>, 
    string, 
    ifstream> * importer = new Importer<
      GeneratorFile<ifstream, string>, 
      HelperWrapper<
        string,
        DoubleList<DoubleNode<string>, string>,
        Tokenizer,
        TokenizerList<
          string,
          CstringWrapper,
          DoubleList<DoubleNode<string>, string>,
          Tokenizer
        >,
        UnqliteWrapper<string>
      >, 
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
    HelperWrapper<
      string,
      DoubleList<DoubleNode<string>, string>,
      Tokenizer,
      TokenizerList<
        string,
        CstringWrapper,
        DoubleList<DoubleNode<string>, string>,
        Tokenizer
      >,
      UnqliteWrapper<string>
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
    HelperWrapper<
      string,
      DoubleList<DoubleNode<string>, string>,
      Tokenizer,
      TokenizerList<
        string,
        CstringWrapper,
        DoubleList<DoubleNode<string>, string>,
        Tokenizer
      >,
      UnqliteWrapper<string>
    >,
    ChainedHashTable<
      DoubleNode<string>, 
      DoubleList<DoubleNode<string>, string>, 
      HashDjb2String<string>,
      DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
      string
    >
    // table
  >(str_adapter, table, table_visited, results);
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
      HelperWrapper<
        string,
        DoubleList<DoubleNode<string>, string>,
        Tokenizer,
        TokenizerList<
          string,
          CstringWrapper,
          DoubleList<DoubleNode<string>, string>,
          Tokenizer
        >,
        UnqliteWrapper<string>
      >,
      // table
      ChainedHashTable<
        DoubleNode<string>, 
        DoubleList<DoubleNode<string>, string>, 
        HashDjb2String<string>,
        DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
        string
      >
      // table for visited nodes 
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
      HelperWrapper<
        string,
        DoubleList<DoubleNode<string>, string>,
        Tokenizer,
        TokenizerList<
          string,
          CstringWrapper,
          DoubleList<DoubleNode<string>, string>,
          Tokenizer
        >,
        UnqliteWrapper<string>
      >,
      // table
      ChainedHashTable<
        DoubleNode<string>, 
        DoubleList<DoubleNode<string>, string>, 
        HashDjb2String<string>,
        DoubleListWalk<DoubleNode<string>, DoubleList<DoubleNode<string>, string> >,
        string
      >
      // table for visited nodes 
    >
    // adapter for index (table here)
  >(adapter);
  // get metrics
  results->insert_right("title", "indexing(seconds)");
  results->insert_right("title", "dataset");
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
  metrics->collect_dataset();
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
  delete tokenizer;
  delete str;
  delete str_adapter;
  delete tokenizer_list;
  delete table_base;
  delete table;
  delete table_visited_walk;
  delete hash_table_visited;
  delete table_visited;
  delete files;
  delete file_read;
  delete importer;
  delete str_timer;
  delete timer;
  delete adapter;
  delete metrics;
  return 0;
}