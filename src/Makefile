

all: main cacher

main : main.cpp veb_array.h eytzinger_array.h sorted_array.h btree_array.h
	g++ -std=c++11 -Wall -O4 -march=native main.cpp -o main

cacher : cacher.cpp 
	g++ -std=c++11 -Wall -O0 cacher.cpp -o cacher


main-debug : main.cpp veb_array.h
	g++ -std=c++11 -Wall -g3 main.cpp -o main-debug

clean :
	rm -f main cacher main-debug

# This is all stuff for doing the test battery
datadir=run_data
magnitudes=00 000 0000 00000 000000 0000000
nums=1 2 3 4 5 6 7 8 9 10
m = 2000000
x = 1
dtypes = uint32 float32 uint64 float64
itypes = uint32 uint64 fast_uint32
ns = $(foreach mag,$(magnitudes), $(foreach x,$(nums),$x$(mag)))
ns += 150000000 200000000 250000000

rawdata	= $(foreach dt, $(dtypes), \
           $(foreach it, $(itypes), \
            $(foreach n, $(ns), $(datadir)/$(dt)-$(it)-$(n)-$(m).dat)))

datafiles = $(datadir)/cpuinfo $(datadir)/free-h $(rawdata)
	
data : main cacher $(datadir) $(datafiles)
	free -h > $(datadir)/free-h

$(datadir) :
	mkdir $@

$(datadir)/cpuinfo : 
	cat /proc/cpuinfo > $@		

$(datadir)/free-h :
	free -h > $@

$(datadir)/%.dat : main
	./main $(subst -, ,$(patsubst $(datadir)/%.dat,%,$(@))) > $@

plots : data
	./make_plots.sh
	#python ./relative.py
	gnuplot "plotter.gp"
