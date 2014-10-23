# Dictionary benchmark
Benchmark of different dictionaries for social network analysis.    
Included are  
1. [Chained hash table](https://github.com/no-glue/chained-hash-table)  
2. [Unqlite](https://github.com/no-glue/unqlite-dictionary)  
3. [AA tree](https://github.com/no-glue/aa-tree)  
## How to run tests with livejournal data set
cd data/livejournal
sh get_livejournal.sh
cd ../..
sh make.sh
sh run_livejournal.sh
sh graphs_livejournal.sh