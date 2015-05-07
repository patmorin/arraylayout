set title t1." running time: ".dt." data with ".it." indices"
set output "run_data/".t1."-".dt."-".it.".svg"
datadir = "run_data"
binary = datadir."/binary-".dt."-".it.".data"
veb = datadir."/veb-".dt."-".it.".data"
eytzinger = datadir."/eytzinger-".dt."-".it.".data"
btree = datadir."/btree-".dt."-".it.".data"
fake = datadir."/fake-".dt."-".it.".data"
plot binary using 1:4 with lines ls 1 title "sorted", \
     eytzinger using 1:4 with lines ls 2 title "Eytzinger", \
     btree using 1:4 with lines ls 3 title "b-tree", \
     veb using 1:4 with lines ls 4 title "vEB", \
     fake using 1:4 with lines ls 5 title "overhead"

