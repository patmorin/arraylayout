import os;
from collections import defaultdict
import matplotlib.pyplot as plt

colors = [
#581B04
#32E526
#CF5BFE
#2D9FCB
#E9D794
#F2397E
#E1530C
#3B7FF8
#1C3355
#20BBA1
#76850B
#772E90
#1D311E
#430329
#9C6111
#AB1B2E
#C5F0C2
#F77AA1
#5F98EE
#615D05


# Have this return true if you want alg to appear in the plot
def i_care(alg):
    return alg.startswith('sorted') or alg.startswith('eytzinger') \
           or alg.startswith('btree16')    
    
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
    algs = [alg for alg in stuff[0] if i_care(alg)]
    data = defaultdict(list)

    # Get the list of values of n that are used.
    ns = sorted([int(x) for x in stuff[3]])

    # Collect the (n, searchtime) pairs for each algorithm.
    dtype = 'uint32'
    itype = 'uint64'
    for alg in algs:
        for n in ns:
            if n in d[alg][dtype][itype]:
                data[alg].append((n, d[alg][dtype][itype][n][1]))

    # Plot everything.
    plt.ioff()
    plt.xscale('log')
    for alg in sorted(algs):
        plt.plot([d[0] for d in data[alg]],
                 [d[1] for d in data[alg]],
                 label=alg, linewidth=2.0)
    plt.legend()
    plt.show()

    
