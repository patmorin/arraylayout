set title dt." data with ".it." indices"
set output "run_data/absolute-".dt."-".it.".svg"
set ylabel "running time (seconds)"
datadir = "run_data"
binary = datadir."/binary-".dt."-".it.".data"
veb = datadir."/veb-".dt."-".it.".data"
eytzinger = datadir."/eytzinger-".dt."-".it.".data"
btree = datadir."/btree-".dt."-".it.".data"
fake = datadir."/fake-".dt."-".it.".data"
plot binary using 1:4 with lines title "sorted", \
     eytzinger using 1:4 with lines title "Eytzinger", \
     btree using 1:4 with lines title "b-tree", \
     veb using 1:4 with lines title "vEB", \
     fake using 1:4 with lines title "overhead"

