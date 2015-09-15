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

markers = [ "o", "s", "p", "*", "H" ]


def make_plot(lines, algs, xmax, filename=None, caches=None, dtype='uint32',
              title=r'running time of $2\times 10^6$ searches on $n$ values',
              ylabel='running time (s)'):

    mapper = [("sorted", ("-", None, None, r'branchy binary search')),
              ("sorted_stl", ("-", None, None, r'\texttt{std::lower\_bound}')),
              ("sorted_bf", ("-", None, None, "branch-free binary search")),
              ("sorted_bfp", ("-", None, None, 
               "branch-free binary search with prefetching")),
              ("fake", ("-", " ", None, "test-harness overhead")),
              ("eytzinger_branchy", ("-", None, None, r'branchy Eytzinger')),
              ("eytzinger_bf", ("-", None, None, r'branch-free Eytzinger')),
              ("eytzinger_bfp_a", ("-", None, None, 
               r'aligned branch-free Eytzinger with prefetching')),
              ("btree16_naive_a", ("-", None, None, r'na\"{\i}ve Btree')),
              ("btree16_a", ("-", None, None, r'unrolled Btree')),
              ("btree16_bf_a", ("-", None, None, 
               r'unrolled branch-free Btree')),
              ("veb", ("-", None, None, r'branchy vEB')),
              ("veb2", ("-", None, None, r'branch-free vEB')),
              ("veb2e", ("-", None, None,
               r'branch-free vEB with early termination')),
              ("eytzinger_bfp", ("-", None, None, r'branch-free Eytzinger with prefetching')),
              ("eytzinger_bfpm_a", ("-", None, None, 
               r'aligned branch-free Eytzinger with masked prefetching')),
              ("eytzinger_bf_a", ("-", None, None, r'aligned branch-free Eytzinger')),
              ("esmixed", ("-", None, None, r'mixed')),
              ("esmixed_pf", ("-", None, None, r'mixed with prefetching')),
              ("placeholder", ('-', None, None, r'XXXX')),
              ("fetcher_1", ("-", None, None, r'deeper prefetching (t=1)')),
              ("fetcher_2", ("-", None, None, r'deeper prefetching (t=2)'))
             ]
    for i in range(1,17):
        mapper.append(("bqtree16_{}".format(i), 
                      ("-", " ", None, r'$(Bk+1)$ary tree ($k={}$)'.format(i))))

    i = 0
    mapper2 = []
    for (k,v) in mapper:
        (line, marker, colour, name) = v
        marker = [marker, markers[i%len(markers)]][marker is None]
        colour = [colour, colours[i%len(colours)]][colour is None]
        mapper2.append((k, (line, marker, colour, name)))
        i += 1
    mapper = dict(mapper2)


    # Snarf the data into a giant nested dictionary.
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
    itype = 'uint64'
    ymax = 0
    for alg in algs:
        for n in ns:
            if n in d[alg][dtype][itype]:
                search_time = d[alg][dtype][itype][n][1]
                if n <= xmax:
                    if search_time > ymax:
                        ymax = search_time
                    data[alg].append((n, search_time))

    # Plot everything.
    width,height = 6.8, 3.5
    if not title or '-bit' in title: height = 2.6
    plt.figure(figsize=(width,height))
    plt.ioff()
    plt.xscale('log', basex=2)
    plt.xlabel('$n$')
    plt.ylabel(ylabel)
    if title: plt.title(title)

    
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
                 label=[lbl,None][alg.startswith('bqtree')
                         and alg not in ['bqtree16_{}'.format(i) for i in range(6,11)]], 
                 #label=lbl,
                 color=clr,
                 linestyle=ls,
                 marker=mrk,
                 linewidth=[2,.6][alg.startswith('bqtree')], 
                 markersize=2.5)

    if caches:
        ylim = plt.ylim()
        plt.ylim(ymax=ylim[1])
        for i in range(len(caches)):
            plt.plot([caches[i]]*2, ylim, label="L{} cache size".format(i+1),
                     linestyle=":", color=colours[i], linewidth=1)

    plt.legend(loc='upper left', framealpha=0.8)
    if filename:
        filename += ".pdf"
        print "Writing {}".format(filename)
        plt.savefig(filename, format='pdf', bbox_inches='tight')
    else:
        plt.show()
    plt.close()

    
if __name__ == "__main__":
    #lines = open('data/lauteschwein-sorted-g++.dat').read().splitlines()
    lines = open('data/lauteschwein-all-g++.dat').read().splitlines()

    # Cache sizes on Intel 4790K
    caches = [2**13, 2**16, 2**21]

    maxn = 2**30

    # Plots of binary search on Intel 4790K
    make_plot(lines, ['sorted', 'sorted_stl'], maxn, 'figs/sorted-i', caches)

    make_plot(lines, ['sorted'], 2**21, 'figs/sorted-ii', caches[:2])

    make_plot(lines, ['sorted', 'sorted_bf', 'fake'], 2**16, 'figs/sorted-iii')

    make_plot(lines, ['sorted', 'sorted_bf'], maxn, 'figs/sorted-iv', caches)

    make_plot(lines, ['sorted', 'sorted_bf', 'sorted_bfp'], maxn,
              'figs/sorted-v', caches)

    # Plots of binary search on Atom 330.
    lines = open('data/scray-sorted-g++.dat').read().splitlines()

    make_plot(lines, ['sorted', 'sorted_bf'], 2**26, 'figs/sorted-atom',
              [2**13, 2**17])

    # Plots of Eytzinger on the Intel 4790K
    lines = open('data/lauteschwein-all-g++.dat').read().splitlines()
    make_plot(lines, ['sorted_bf', 'sorted_bfp', 
                      'eytzinger_branchy', 'eytzinger_bf'], maxn, 
        'figs/eytzinger-i', caches)

    make_plot(lines, ['sorted_bfp', 'eytzinger_branchy', 'eytzinger_bf', 
                      'eytzinger_bfp', 'eytzinger_bfp_a'], maxn, 'figs/eytzinger-ii', caches)

    make_plot(lines, ['sorted_bf', 'sorted_bfp', 'eytzinger_branchy',  
                      'eytzinger_bf', 'eytzinger_bfp_a'], 2**16, 
                      'figs/eytzinger-iii', caches[:1])

    make_plot(lines, ['sorted_bf', 'eytzinger_bfp_a', 'btree16_naive_a', 
                      'btree16_a', 'btree16_bf_a'], maxn, 'figs/btree-i', 
              caches)

    make_plot(lines, ['eytzinger_bfp_a', 'btree16_naive_a', 'btree16_a', 
                      'btree16_bf_a', 'sorted_bf'], 2**20, 'figs/btree-ii', caches[:2])

    make_plot(lines, ['veb', 'veb2'], maxn, 'figs/veb-all', caches)

    make_plot(lines, ['btree16_bf_a', 'eytzinger_bfp_a', 
                      'veb', 'veb2'], maxn, 'figs/veb-i', caches)

    # 64 bit results
    lines = open('data/lauteschwein-all64-g++.dat').read().splitlines()
    make_plot(lines, ['eytzinger_bfp_a', 'btree16_bf_a', 'sorted_bfp'], 
              2**31, 'figs/64bit', [x/2 for x in caches], 'uint64',
              r'running time of $2\times 10^6$ searches on $n$ 64-bit values')

    # 128 bit results
    lines = open('data/lauteschwein-all128-g++.dat').read().splitlines()    
    make_plot(lines, ['eytzinger_bfp_a', 'btree16_bf_a', 'sorted_bfp'], 
              2**30, 'figs/128bit', [x/4 for x in caches], 'uint128',
              r'running time of $2\times 10^6$ searches on $n$ 128-bit values')


    # multithread results
    lines = open('data/lauteschwein-threads-2-g++.dat').read().splitlines()    
    make_plot(lines, ['eytzinger_bfp_a', 'btree16_bf_a'], 
              2**30, 'figs/threads2', caches, 'uint32', '', 
              'completion time for 2 threads (s)')
    lines = open('data/lauteschwein-threads-4-g++.dat').read().splitlines()    
    make_plot(lines, ['eytzinger_bfp_a', 'btree16_bf_a'], 
              2**30, 'figs/threads4', caches, 'uint32', '',
              'completion time for 4 threads (s)')
    lines = open('data/lauteschwein-threads-8-g++.dat').read().splitlines()    
    make_plot(lines, ['eytzinger_bfp_a', 'btree16_bf_a'], 
              2**30, 'figs/threads8', caches, 'uint32', '',
              'completion time for 8 threads (s)')

    # bqtree results
    lines = open('data/lauteschwein-bqtrees-g++.dat').read().splitlines() \
            + open('data/lauteschwein-all-g++.dat').read().splitlines()
    make_plot(lines, ['bqtree16_{}'.format(i) for i in range(2,17)] 
                     + ['eytzinger_bfp_a', 'btree16_bf_a', 'bqtree16_1'], 
              2**30, 'figs/bktrees-i', [], 'uint32')
    make_plot(lines, ['bqtree16_{}'.format(i) for i in range(6,11)] 
                     + ['eytzinger_bfp_a', 'btree16_bf_a'], 
              2**30, 'figs/bktrees-ii', [], 'uint32')

    # using a prefetch mask on the Intel E3-1230
    lines = open('data/mirzakhani.dat').read().splitlines()
    make_plot(lines, ['eytzinger_bfp_a', 'eytzinger_bfpm_a', 'btree16_bf_a'], 
              2**30, 'figs/masking-i', caches)
    make_plot(lines, ['eytzinger_bfp_a', 
                      'eytzinger_bfpm_a', 'btree16_bf_a'], 
              2**21, 'figs/masking-ii', caches[:2])

    # using a prefetch mask on the Intel 4790K
    lines = open('data/lauteschwein-masking-mixed.dat').read().splitlines()
    make_plot(lines, ['eytzinger_bfp_a', 'eytzinger_bfpm_a', 'btree16_bf_a'], 
              2**30, 'figs/masking-iii', caches)
    make_plot(lines, ['eytzinger_bfp_a', 'eytzinger_bfpm_a', 'btree16_bf_a'], 
              2**21, 'figs/masking-iv', caches[:2])

    # Eytzinger versus mixed
    lines = open('data/mixed-tests.dat').read().splitlines()    
    make_plot(lines, ['eytzinger_bf_a', 'sorted_bf', 'esmixed'],
              2**30, 'figs/mixed-i', caches)
    make_plot(lines, ['eytzinger_bfp_a', 'esmixed_pf'], 
              2**30, 'figs/mixed-ii', caches)


    for s in [4, 8, 16]:
        lines = open('data/tmp2-{}.dat'.format(s)).read().splitlines()
        make_plot(lines, ['eytzinger_bfp_a'] + 
                         ['fetcher_{}'.format(i) for i in [1,2]],
                  2**30, 'figs/fetchers-{}-i'.format(s), 
                  [4*x/s for x in caches], 'uint{}'.format(8*s),
                  r'running time of $2\times10^6$ searches on $n$ {}-bit values'.format(s*8))
        make_plot(lines, ['eytzinger_bfp_a'] +
                         ['fetcher_{}'.format(i) for i in [1,2]],
                  2**23/s, 'figs/fetchers-{}-ii'.format(s), 
                  [4*x/s for x in caches[:2]], 'uint{}'.format(8*s),
                  r'running time of $2\times10^6$ searches on $n$ {}-bit values'.format(s*8))


