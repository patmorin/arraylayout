version=0.1
CC=g++
CFLAGS=-std=c++11 -Wall -O4 -march=native 

all: main cacher

distrib: arraylayout.tgz

headerfiles = base_array.h veb_array.h eytzinger_array.h sorted_array.h btree_array.h mixed_array.h bktree_array.h

mainfiles = main.cpp main-mt.cpp $(headerfiles)
main : $(mainfiles)
	$(CC) $(CFLAGS) main.cpp -o main

main-mt : $(mainfiles)
	$(CC) $(CFLAGS) -pthread main-mt.cpp -o main-mt -pthread

main-debug : $(mainfiles)
	g++ -std=c++11 -Wall -g3 main.cpp -o main-debug

cacher : cacher.cpp 
	g++ -std=c++11 -Wall -O4 cacher.cpp -o cacher

example: example.cpp $(headerfiles)
	g++ -std=c++11 -Wall example.cpp -o example

arraylayout-$(VERSION).tgz : $(mainfiles) cacher.cpp Makefile README
	$(eval dirname := arraylayout-$(version))
	rm -rf $(dirname)
	mkdir $(dirname)
	cp $^ $(dirname)/
	tar czvf arraylayout-$(VERSION).tgz $(dirname)

clean :
	rm -f main cacher main-debug

# This is all stuff for doing the test battery
datadir = run_data
nums = 1 2 3 4 5 6 7 8 9 10
m = 2000000
x = 1
dtypes32 = uint32
itypes = fast_uint32 uint64
ns32 = 1 2 3 5 6 7 10 12 15 19 25 31 39 50 63 79 100 125 158 199 251 316 398 501 630 794 1000 1258 1584 1995 2511 3162 3981 5011 6309 7943 10000 12589 15848 19952 25118 31622 39810 50118 63095 79432 100000 125892 158489 199526 251188 316227 398107 501187 630957 794328 1000000 1258925 1584893 1995262 2511886 3162277 3981071 5011872 6309573 7943282 10000000 12589254 15848931 19952623 25118864 31622776 39810717 50118723 63095734 79432823 100000000 125892541 158489319 199526231 251188643
# 316227766, 398107170, 501187233, 630957344, 794328234, 1000000000, 1258925411, 1584893192

rawdata = $(foreach dt, $(dtypes32), \
           $(foreach it, $(itypes), \
            $(foreach n, $(ns32), $(datadir)/$(dt)-$(it)-$(n)-$(m).t)))

dtypes64 = uint64
ns64 = 1 2 3 5 6 7 10 12 15 19 25 31 39 50 63 79 100 125 158 199 251 316 398 501 630 794 1000 1258 1584 1995 2511 3162 3981 5011 6309 7943 10000 12589 15848 19952 25118 31622 39810 50118 63095 79432 100000 125892 158489 199526 251188 316227 398107 501187 630957 794328 1000000 1258925 1584893 1995262 2511886 3162277 3981071 5011872 6309573 7943282 10000000 12589254 15848931 19952623 25118864 31622776 39810717 50118723 63095734 79432823 100000000 125892541
rawdata += $(foreach dt, $(dtypes64), \
            $(foreach it, $(itypes), \
             $(foreach n, $(ns64), $(datadir)/$(dt)-$(it)-$(n)-$(m).t)))

dtypes128 = uint128
ns128 = 1 2 3 5 6 7 10 12 15 19 25 31 39 50 63 79 100 125 158 199 251 316 398 501 630 794 1000 1258 1584 1995 2511 3162 3981 5011 6309 7943 10000 12589 15848 19952 25118 31622 39810 50118 63095 79432 100000 125892 158489 199526 251188 316227 398107 501187 630957 794328 1000000 1258925 1584893 1995262 2511886 3162277 3981071 5011872 6309573 7943282 10000000 12589254 15848931 19952623 25118864 31622776 39810717 50118723 63095734
rawdata += $(foreach dt, $(dtypes128), \
            $(foreach it, $(itypes), \
             $(foreach n, $(ns128), $(datadir)/$(dt)-$(it)-$(n)-$(m).t)))

datafiles = $(datadir)/cpuinfo $(datadir)/free-h $(datadir)/uname-a \
            $(datadir)/gcc-v $(datadir)/cacher.data $(datadir)/sha1sums  \
            $(datadir)/main.s $(rawdata)

data : main cacher $(datadir) $(datafiles) run_data.tgz
	echo "Done! Please send run_data.tgz to morin@scs.carleton.ca"

$(datadir) :
	mkdir $@

$(datadir)/sha1sums :
	sha1sum *.cpp *.h > $@

$(datadir)/cpuinfo : 
	cat /proc/cpuinfo > $@		

$(datadir)/free-h :
	free -h > $@

$(datadir)/uname-a :
	uname -a > $@

$(datadir)/gcc-v :
	gcc -march=native -Q --help=target > $@
	echo | gcc -dM -E - -march=native >> $@

$(datadir)/main.s : $(mainfiles)
	gcc $(CFLAGS) -S -c main.cpp -o $@

$(datadir)/cacher.data : cacher
	./cacher > $@

$(datadir)/%.t : main
	./main $(subst -, ,$(patsubst $(datadir)/%.t,%,$(@))) \
		>> $(datadir)/alldata.dat 
	touch $@

run_data.tgz : $(datadir) $(datafiles)
	tar czvf run_data.tgz run_data --exclude "*.t"

clean-data :
	rm -rf $(datadir) run_data.tgz


