import os;
from collections import defaultdict
import matplotlib.pyplot as plt

# Some maximally dissimilar colors from iwanthue: http://goo.gl/abF97 .
colours = ['#1FAC7E', '#6D5AD8', '#FD692A', '#F9498D', '#965153',
           '#FA796D', '#AD1E57']

styles = ['-', '--', ':']

markers = [ "o", "s", "p", "*" ]


# Have this return true if you want alg to appear in the plot
def i_care(alg):
    return alg.startswith('eytzinger') or alg.startswith('sorted') \
           or alg.startswith('btree16')  or alg.startswith('veb')  
    
if __name__ == "__main__":
    # Snarf the data into a giant nested dictionary.
    datadir = 'run_data'
    filename = 'alldata.dat'
    fullname = datadir + os.path.sep + filename
    lines = open(fullname).read().splitlines()

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
    algs = sorted([alg for alg in stuff[0] if i_care(alg)])
    data = defaultdict(list)

    # Get the list of values of n that are used.
    ns = sorted([int(x) for x in stuff[3]])

    # Collect the (n, searchtime) pairs for each algorithm.
    dtype = 'uint32'
    itype = 'uint64'
    best = defaultdict(lambda: ('none', 10.**6))
    mx = 0
    for alg in algs:
        for n in ns:
            if n in d[alg][dtype][itype]:
                search_time = d[alg][dtype][itype][n][1]
                mx = max(mx, search_time)
                data[alg].append((n, search_time))
                if search_time < best[n][1]:
                    best[n] = (alg, search_time)

    # Plot everything.
    plt.ioff()
    plt.xscale('log')
    idx = 0
    for alg in algs:
        plt.plot([d[0] for d in data[alg]],
                 [d[1] for d in data[alg]],
                 label = alg, linewidth = 1.5, 
                 color = colours[idx % len(colours)], 
                 linestyle = styles[idx % len(styles)],
                 marker = markers[idx % len(markers)],
                 markersize = 4.0)
        idx += 1

    # Plot of the winners
    for n in ns:
       if best[n][0] in algs:
           idx = algs.index(best[n][0])
           plt.plot([n], [mx+.5], color = colours[idx % len(colours)],
                    marker = markers[idx % len(markers)],
                    markersize = 8.0)

    plt.legend()
    plt.show()

    
