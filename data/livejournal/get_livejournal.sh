wget http://snap.stanford.edu/data/bigdata/communities/com-lj.ungraph.txt.gz
gzip -d com-lj.ungraph.txt.gz
mv com-lj.ungraph.txt original
tail -n +5 original > tmp
mv tmp original
split -l 1000000 original livejournal
find $(pwd) -iname "livejournal*" > to_read
tail -n +2 to_read > tmp
mv tmp to_read
rm original