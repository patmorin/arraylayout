set term svg size 800 600
set output "run_data/cacher.svg"
set logscale x 10 
set title "cache profile"
set ylabel "time for m random accesses on array of size n (s)"
set xlabel "log(n)/log(10)"
set key off
set format x "%L"
plot "run_data/cacher.data" with lines
