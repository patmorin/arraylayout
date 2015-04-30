
all: main cacher

main : main.cpp veb_array.h
	g++ -std=c++11 -Wall -O4 -march=native main.cpp -o main

cacher : cacher.cpp 
	g++ -std=c++11 -Wall -O0 cacher.cpp -o cacher


main-debug: main.cpp veb_array.h
	g++ -std=c++11 -Wall -g3 main.cpp -o main-debug

clean:
	rm -f main cacher main-debug
