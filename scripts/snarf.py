import os
import sys
from collections import defaultdict
import matplotlib as mpl


# Use TeX to render output
#from matplotlib import rc
#rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
## for Palatino and other serif fonts use:
#rc('font',**{'family':'serif','serif':['Palatino']})
#rc('text', usetex=True)

mpl.use("pgf")
pgf_with_pdflatex = {
	"font.family": "serif",
    "font.size": 9,
    "text.usetex" : True,
    "pgf.rcfonts": False,
    "pgf.texsystem": "pdflatex",
    "pgf.preamble": [
         r"\usepackage[utf8]{inputenc}",
         r"\usepackage[T1]{fontenc}",
         r"\usepackage{kpfonts}",
         ]
}
mpl.rcParams.update(pgf_with_pdflatex)

import matplotlib.pyplot as plt

# Some nice colours from ColorBrewer2
colours = ['#a6cee3', '#1f78b4', '#b2df8a', '#33a02c', '#fb9a99', '#e31a1c',
           '#fdbf6f', '#ff7f00', '#cab2d6', '#6a3d9a', '#ffff99', '#b15928']
c0 = [colours[i] for i in range(len(colours)) if i % 2 == 0]
c1 = [colours[i] for i in range(len(colours)) if i % 2 == 1]
colours = c1 + c0


styles = ['-', '--', ':']

markers = [ "o", "s", "p", "*" ]


# Have this return true if you want alg to appear in the plot
def i_care(alg):
    return alg in ['sorted', 'sorted_stl']
    return alg.startswith('sorted')
    return alg.startswith('eytzinger') or alg.startswith('sorted_bf') \
           or alg.startswith('btree16')  or alg.startswith('veb')  

def make_plot(lines, algs, xmax, filename=None, caches=None):
    # Snarf the data into a giant nested dictionary.
    

    mapper = dict([("sorted", ("-", "o", colours[0], 
                    r'na\"{\i}ve binary search')),
                   ("sorted_stl", ("-", "p", colours[1], 
                    r'\texttt{stl::lower\_bound}')),
                   ("sorted_bf", ("-", "s", colours[2], 
                    "branch-free binary search")),
                   ("sorted_bfp", ("-", "*", colours[3], 
                    "branch-free binary search with prefetching")),
                   ("fake", ("-", " ", colours[4], 
                    "test-harness overhead")),
                   ("eytzinger_branchy", ("-", "p", colours[5], 
                     r'na\"{\i}ve Eytzinger')),
                   ("eytzinger_bf", ("-", "s", colours[6], 
                     r'branch-free Eytzinger')),
                   ("eytzinger_bfp_a", ("-", "H", colours[0], 
                     r'aligned branch-free Eytzinger with prefetching')),
                   ("btree16_a", ("-", "o", colours[1], 
                     r'na\"{\i}ve 17-tree')),
                   ("btree16_bf_a", ("-", "p", colours[2], 
                     r'branch-free 17-tree')),
                  ])


    # Now I like default dicts.
    def factory(): return defaultdict(factory)
    d = defaultdict(factory)

    # This keeps track of all different parameters.
    stuff = [set() for _ in range(5)]

    
    for line in lines:
        line = line.split()
        for i in range(5): stuff[i].add(line[i])
        (alg, dt, it, n, m, btime, stime, cs) = line
        d[alg][dt][it][int(n)] = (float(btime), float(stime), cs)	

    # Get the list of algorithms we care about.
    # algs = sorted([alg for alg in stuff[0] if i_care(alg)])
    data = defaultdict(list)

    # Get the list of values of n that are used.
    ns = sorted([int(x) for x in stuff[3]])

    # Collect the (n, searchtime) pairs for each algorithm.
    dtype = 'uint32'
    itype = 'uint64'
    best = defaultdict(lambda: ('none', 10.**6))
    ymax = 0
    for alg in algs:
        for n in ns:
            if n in d[alg][dtype][itype]:
                search_time = d[alg][dtype][itype][n][1]
                if n <= xmax:
                    if search_time > ymax:
                        ymax = search_time
                    data[alg].append((n, search_time))
                    if search_time < best[n][1]:
                        best[n] = (alg, search_time)

    # Plot everything.
    plt.figure(figsize=(6.8,3.5))
    plt.ioff()
    plt.xscale('log', basex=2)
    plt.xlabel('$n$')
    plt.ylabel('running time (s)')
    plt.title(r'running time of $2\times 10^6$ searches $n$ values')
    plt.xlim(1, xmax)
    idx = 0
    for alg in algs:
        if alg in mapper:
            (ls, mrk, clr, lbl) = mapper[alg]
        else:
            lbl = alg
            clr = colours[idx % len(colours)]
            ls = styles[idx % len(styles)]
            mrk = markers[idx % len(markers)]
            idx += 1
        plt.plot([d[0] for d in data[alg]],
                 [d[1] for d in data[alg]],
                 label=lbl, 
                 color=clr,
                 linestyle=ls,
                 marker=mrk,
                 linewidth=2, 
                 markersize=2.5)

    if caches:
        ylim = plt.ylim()
        plt.ylim(ymax=ylim[1])
        for i in range(len(caches)):
            plt.plot([caches[i]]*2, ylim, label="L{} cache size".format(i+1),
                     linestyle=":", color=colours[i], linewidth=1)
    # Plot of the winners
    """for n in ns:
       if best[n][0] in algs:
           idx = algs.index(best[n][0])
           plt.plot([n], [mx+.5], color = colours[idx % len(colours)],
                    marker = markers[idx % len(markers)],
                    markersize = 8.0)
    """
    plt.legend(loc='upper left')
    if filename:
        filename += ".pdf"
        print "Writing {}".format(filename)
        plt.savefig(filename, format='pdf', bbox_inches='tight')
    else:
        plt.show()
    plt.close()

    
if __name__ == "__main__":
    lines = open('data/lauteschwein-sorted-g++.dat').read().splitlines()

    # Cache sizes on Intel 4790K
    caches = [2**13, 2**16, 2**21]

    # Plots of binary search on Intel 4790K
    make_plot(lines, ['sorted', 'sorted_stl'], 2**27, 'figs/sorted-i', caches)

    make_plot(lines, ['sorted'], 2**21, 'figs/sorted-ii', caches)

    make_plot(lines, ['sorted', 'sorted_bf', 'fake'], 2**16, 'figs/sorted-iii')

    make_plot(lines, ['sorted', 'sorted_bf'], 2**27, 'figs/sorted-iv', caches)

    make_plot(lines, ['sorted', 'sorted_bf', 'sorted_bfp'], 2**27,
              'figs/sorted-v', caches)

    # Plots of binary search on Atom 330.
    lines = open('data/scray-sorted-g++.dat').read().splitlines()

    make_plot(lines, ['sorted', 'sorted_bf'], 2**27, 'figs/sorted-atom',
              [2**13, 2**17])

    # Plots of Eytzinger on the Intel 4790K
    lines = open('data/lauteschwein-eytzinger-clang.dat').read().splitlines()
    lines += open('data/lauteschwein-sorted-g++.dat').read().splitlines()
    make_plot(lines, ['eytzinger_branchy', 'eytzinger_bf', 'sorted_bfp'], 2**27, 
        'figs/eytzinger-i', caches)

    make_plot(lines, ['eytzinger_branchy', 'eytzinger_bf', 'sorted_bfp', 'eytzinger_bfp_a'], 
              2**27, 'figs/eytzinger-ii', caches)

    lines += open('data/lauteschwein-btree-g++.dat').read().splitlines()
    lines += open('data/lauteschwein-sorted-g++.dat').read().splitlines()
    make_plot(lines, ['btree16_a', 'btree16_bf_a', 'sorted_bf', 'eytzinger_bfp_a'], 2**27, 'figs/btree-i', caches)

