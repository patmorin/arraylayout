#!/bin/bash

./make_plots.sh
gnuplot plotter.gp
gnuplot cacher.gp
./make_html.sh > run_data/index.html
model=`grep 'model name' run_data/cpuinfo | head -1`
d=`basename $PWD`
echo "<li><a href='$d/run_data/'>$model</a></li>"

