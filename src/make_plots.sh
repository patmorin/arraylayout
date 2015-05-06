#!/bin/bash

dtypes=("uint32" "float32" "uint64" "float64")
itypes=("uint32" "uint64" "fast_uint32")
algs=("fake" "binary" "veb" "eytzinger" "tree")

m=2000000

datadir="run_data"
op="search"
for dt in ${dtypes[@]}; do
  for it in ${itypes[@]}; do
    for alg in ${algs[@]}; do 
      fname="${datadir}/${dt}-${it}-${alg}-${op}_unsorted.data"
      echo -n "" > "$fname"
      echo "$dt $it $alg"
      for f in run_data/${dt}-${it}-*-${m}.dat; do
        n=`basename "$f"`
        n=${n%-${m}.dat}	
        n=${n#${dt}-${it}-}	
        t=`grep "${alg}.*searches" "$f" | awk '{print $7}'`
        echo $n $t >> "$fname"
      done
      sort -n "$fname" > "${datadir}/${dt}-${it}-${alg}-${op}.data"
      rm -f "$fname"
    done
  done
done

