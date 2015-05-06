

all: main cacher

mainfiles = main.cpp veb_array.h eytzinger_array.h sorted_array.h btree_array.h

main : $(mainfiles)
	g++ -std=c++11 -Wall -O4 -march=native main.cpp -o main

main-debug : $(mainfiles)
	g++ -std=c++11 -Wall -g3 main.cpp -o main-debug

cacher : cacher.cpp 
	g++ -std=c++11 -Wall -O4 cacher.cpp -o cacher

clean :
	rm -f main cacher main-debug

# This is all stuff for doing the test battery
datadir=run_data
magnitudes=00 000 0000 00000 000000 0000000
nums=1 2 3 4 5 6 7 8 9 10
m = 2000000
x = 1
dtypes = uint32 float32 uint64 float64 int128
itypes = uint32 uint64 fast_uint32
ns = $(foreach mag,$(magnitudes), $(foreach x,$(nums),$x$(mag)))
ns += 150000000 200000000 250000000

rawdata	= $(foreach dt, $(dtypes), \
           $(foreach it, $(itypes), \
            $(foreach n, $(ns), $(datadir)/$(dt)-$(it)-$(n)-$(m).t)))

datafiles = $(datadir)/cpuinfo $(datadir)/free-h $(datadir)/uname-a \
            $(datadir)/gcc-v $(datadir)/cacher.data $(rawdata)
	
data : main cacher $(datadir) $(datafiles)
	free -h > $(datadir)/free-h

$(datadir) :
	mkdir $@

$(datadir)/cpuinfo : 
	cat /proc/cpuinfo > $@		

$(datadir)/free-h :
	free -h > $@

$(datadir)/uname-a :
	uname -a > $@

$(datadir)/gcc-v :
	gcc -march=native -Q --help=target > $@

$(datadir)/cacher.data : cacher
	./cacher > $@

$(datadir)/%.t : main
	./main $(subst -, ,$(patsubst $(datadir)/%.t,%,$(@))) \
		>> $(datadir)/alldata.dat 
	touch $@

clean-data :
	rm -rf $(datadir)

plots : data
	./make_plots.sh
	#python ./relative.py
	gnuplot "plotter.gp"

html : plots
	./make_html.sh


