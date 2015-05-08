#!/bin/bash -ex

scriptdir=../scripts

tar xvf run_data.tgz
chmod a+x run_data
${scriptdir}/make_plots.sh
python ${scriptdir}/relative.py
gnuplot ${scriptdir}/plotter.gp
gnuplot ${scriptdir}/cacher.gp
${scriptdir}/make_html.sh > run_data/index.html
model=`grep 'model name' run_data/cpuinfo | head -1`
d=`basename $PWD`
echo "Paste this into your HTML file"
echo "           <li><a href='$d/run_data/'>$model</a></li>"

