wget http://snap.stanford.edu/data/as-skitter.txt.gz
gzip -d as-skitter.txt.gz
mv as-skitter.txt original
tail -n +6 original > tmp
mv tmp original
split -l 1000000 original skitter
find $(pwd) -iname "skitter*" > to_read
tail -n +2 to_read > tmp
mv tmp to_read
rm original