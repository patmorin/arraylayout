set term svg size 800 600
set format x "%L"
set logscale x 10
set xlabel "log(n)/log(10)"
set yrange [0:]


t1="absolute"
set ylabel "running time (seconds)"

dt="uint32"
it="uint32"
load "plotteur.gp"

dt="uint32"
it="uint64"
load "plotteur.gp"

dt="uint64"
it="uint32"
load "plotteur.gp"

dt="uint64"
it="uint64"
load "plotteur.gp"

dt="float32"
it="uint32"
load "plotteur.gp"

dt="float64"
it="uint32"
load "plotteur.gp"

dt="float32"
it="uint64"
load "plotteur.gp"

dt="float64"
it="uint64"
load "plotteur.gp"

dt="int128"
it="uint32"
load "plotteur.gp"

dt="int128"
it="uint64"
load "plotteur.gp"



t1="relative"
set ylabel "speedup (over sorted array)"

dt="uint32"
it="uint32-rel"
load "plotteuse.gp"

dt="uint32"
it="uint64-rel"
load "plotteuse.gp"

dt="uint64"
it="uint32-rel"
load "plotteuse.gp"

dt="uint64"
it="uint64-rel"
load "plotteuse.gp"

dt="float32"
it="uint32-rel"
load "plotteuse.gp"

dt="float64"
it="uint32-rel"
load "plotteuse.gp"

dt="float32"
it="uint64-rel"
load "plotteuse.gp"

dt="float64"
it="uint64-rel"
load "plotteuse.gp"

dt="int128"
it="uint32-rel"
load "plotteuse.gp"

dt="int128"
it="uint64-rel"
load "plotteuse.gp"







#
#    EOF
