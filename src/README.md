These are the source files used to generate data in the paper:

  ARRAY LAYOUTS FOR COMPARISON-BASED SEARCHING
  by Paul-Virak Khuong and Pat Morin

The implementations here are not exactly ready for industrial use, but 
they are here for you to play with.  

If you just want a simple example, look in the file example.cpp and 

    make example

If you want to do some timing tests, look in file main.cpp and 

    make main

If you want to see how long it takes to do 2000000 searches on an array
containing 100000000 32-bit integers, you can do

    ./main uint32 uint64 100000000 2000000 | awk '{printf("%-20s %f\n", $1, $7)}'

This will give you a lot of data, you probably want to open main.cpp, go
into the run_tests(n,m) function and comment out the layouts you're not 
interested in.
