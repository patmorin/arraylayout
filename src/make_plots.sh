#!/bin/bash

dtypes=("uint32" "float32" "uint64" "float64" "int128")
itypes=("uint32" "uint64")
algs=("fake" "binary" "veb" "eytzinger" "btree")

m=2000000

datadir="run_data"
op="search"
for dt in ${dtypes[@]}; do
  for it in ${itypes[@]}; do
    for alg in ${algs[@]}; do 
      fname="${datadir}/${alg}-${dt}-${it}.data"
      grep "${alg} ${dt} ${it}" ${datadir}/alldata.dat \
         | cut -d' ' -f 4- > $fname
    done
  done
done

