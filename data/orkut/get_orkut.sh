wget http://snap.stanford.edu/data/bigdata/communities/com-orkut.ungraph.txt.gz
gzip -d com-orkut.ungraph.txt.gz
mv com-orkut.ungraph.txt original
tail -n +5 original > tmp
mv tmp original
split -l 1000000 original orkut
find $(pwd) -iname "orkut*" > to_read
tail -n +2 to_read > tmp
mv tmp to_read
rm original