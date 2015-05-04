#!/bin/bash

algs=("fake" "sorted" "veb" "eytzinger" "17-tree")

for alg in ${algs[@]}; do 
  echo -n "" > "run_data/${alg}_unsorted.data"
  echo "$alg"
  for f in run_data/*.dat; do
    n=`basename "$f"`
    n=${n%.dat}	
    t=`grep 'veb.*searches' "$f" | awk '{print $7}'`
  	echo $n $t | tee -a "run_data/${alg}_unsorted.data" 
  done
  sort -n "run_data/${alg}_unsorted.data" > "run_data/${alg}.data"
done
