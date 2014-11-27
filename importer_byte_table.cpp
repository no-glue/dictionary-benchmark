#define SIZE 4294967295

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <time.h>
#include <math.h>
#include "byte_table.h"
#include "filter.h"
#include "byte_table_to_list.h"
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
  CstringWrapper * str = new CstringWrapper(), * str_timer = new CstringWrapper(), * str_table_to_list = new CstringWrapper();
  HashDjb2String<string> * hash = new HashDjb2String<string>();
  Tokenizer * tokenizer_to_list = new Tokenizer(), * tokenizer_to_list_key = new Tokenizer();
  // str for c strings
  ByteTable<
   CstringWrapper,
   HashDjb2String<string>
  > * table_base = new ByteTable<
   CstringWrapper,
   HashDjb2String<string>
  >(SIZE / 2, str, hash);
  // table base
  ByteTableToList<
    Tokenizer,
    DoubleList<DoubleNode<string>, string>,
    CstringWrapper
  > * table_to_list = new ByteTableToList<
    Tokenizer,
    DoubleList<DoubleNode<string>, string>,
    CstringWrapper
  >(tokenizer_to_list, tokenizer_to_list_key, str_table_to_list);
  // table to list
  ByteTableAsList<
    string,
    DoubleList<DoubleNode<string>, string>,
    ByteTableToList<
      Tokenizer, 
      DoubleList<DoubleNode<string>, 
      string>, 
      CstringWrapper
    >,
    ByteTable<
      CstringWrapper, 
      HashDjb2String<string>
    >
  > * table = new ByteTableAsList<
    string,
    DoubleList<DoubleNode<string>, string>,
    ByteTableToList<
      Tokenizer, 
      DoubleList<DoubleNode<string>, 
      string>, 
      CstringWrapper
    >,
    ByteTable<
      CstringWrapper, 
      HashDjb2String<string>
    >
  >(table_to_list, table_base);
  // table
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
      DoubleList<DoubleNode<string>, string>,
      ByteTableToList<
        Tokenizer, 
        DoubleList<DoubleNode<string>, 
        string>, 
        CstringWrapper
      >,
      ByteTable<
        CstringWrapper, 
        HashDjb2String<string>
      >
    >, 
    DecoratorFileRead<ostream, string>, 
    string, 
    ifstream> * importer = new Importer<
      GeneratorFile<ifstream, string>, 
      ByteTableAsList<
        string,
        DoubleList<DoubleNode<string>, string>,
        ByteTableToList<
          Tokenizer, 
          DoubleList<DoubleNode<string>, 
          string>, 
          CstringWrapper
        >,
        ByteTable<
          CstringWrapper, 
          HashDjb2String<string>
        >
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
  timer->set_sooner(time(NULL));
  importer->import(files, table, file_read);
  timer->set_later(time(NULL));
  delete str;
  delete str_timer;
  delete str_table_to_list;
  delete hash;
  delete tokenizer_to_list;
  delete tokenizer_to_list_key;
  delete table_base;
  delete table_to_list;
  delete table;
  delete files;
  delete file_read;
  delete importer;
  delete timer;
  return 0;
}
