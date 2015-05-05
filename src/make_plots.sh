#!/bin/bash

algs=("fake" "binary" "veb" "eytzinger" "17-tree")

datadir="run_data"
op="search"
for alg in ${algs[@]}; do 
  fname="${datadir}/${alg}-${op}_unsorted.data"
  echo -n "" > "$fname"
  echo "$alg"
  for f in run_data/*.dat; do
    n=`basename "$f"`
    n=${n%.dat}	
    t=`grep "${alg}.*searches" "$f" | awk '{print $7}'`
    echo $n $t >> "$fname"
  done
  sort -n "$fname" > "${datadir}/${alg}-${op}.data"
done
