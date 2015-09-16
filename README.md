# arraylayout
Experiments with memory layouts for binary search

If  you're curious, you can following this project's progress in
[my notebook](http://nbviewer.ipython.org/github/patmorin/arraylayout/blob/master/src/arraylayouts.ipynb).

## About
This project is about trying different memory layouts for searching in an array, with a focus on improving performance for the most common-case: When the input fits entirely in RAM. The layouts we try are:

1. sorted: The usual sorted array on which we apply binary search
2. eytzinger: The Eytzinger (or BFS) layout most commonly used implicit binary heaps
3. btree: A (B+1)-ary variant of the Eytzinger layout
4. veb: The van Emde Boas layout from the cache-oblivious literature

## Quick start
To run an experiment on your own (linux) machine (with g++ installed):

    cd src
    make main
    ./main uint32 uint32 100000000 10000000

This will test the cost of performing ten million searches in an array of one hundred million integers.  You'd better have at least 800MB of free RAM, which you can check with

    free -h

## Results

A webpage with some collected results is being maintained here:

http://cglab.ca/~morin/misc/arraylayout/

