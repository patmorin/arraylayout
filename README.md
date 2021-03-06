# arraylayout
Experiments with memory layouts for binary search.

These are the sources (LaTeX, C++, and Python) for the paper

  [ARRAY LAYOUTS FOR COMPARISON-BASED SEARCHING](http://arxiv.org/abs/1509.05053)

  by Paul-Virak Khuong and Pat Morin


## About
This project is about trying different memory layouts for searching in
an array, with a focus on improving performance for the most common-case:
When the input fits entirely in RAM. The layouts we try are:

1. sorted: The usual sorted array on which we apply binary search
2. eytzinger: The Eytzinger (or BFS) layout most commonly used implicit
   binary heaps
3. btree: A (B+1)-ary variant of the Eytzinger layout
4. veb: The van Emde Boas layout from the cache-oblivious literature

## Quick start
To run an experiment on your own (linux) machine (with g++ installed):

    cd src
    make main
    ./main uint32 uint32 100000000 10000000

This will test the cost of performing ten million searches in an array
of one hundred million integers.  You'd better have at least 800MB of
free RAM, which you can check with

    free -h

## Replicated Computational Results

This work is in the process of earning a [Replicated Computational
Result](http://jea.acm.org/rcr_initiative.cfm) certificate from the
[ACM Journal of Experimental Algorithmics](http://jea.acm.org/).
To achieve this, we have developed scripts that allow anyone with a
suitable system to reproduce the computational results (in this case,
figures) in the paper.

If you want to try and reproduce our results, execute

    ./rcr

For this to work, you will need (at least) the following software installed

- g++
- lscpu
- free
- numactl
- python with matplotlib
- pdflatex

To fully replicate the experiments in the paper, you will need at least 15GB
of free RAM. The experiments will scale down to use at most 2/3 of your
available RAM otherwise.

Using the preceding script will generate PDF and SVG figures in the
scripts/figs-rcr directory.  You can view the resulting SVG files in a
browser by opening scripts/figs-rcr/index.html

## Results

A webpage describing this work and with some collected results is being
maintained here:

http://cglab.ca/~morin/misc/arraylayout-v2/


