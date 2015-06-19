import os
import itertools

if __name__ == "__main__":
    base = 1.258925412
    dtypes = [("uint32", 4)]
    itypes = ["uint64"]
    n = base;
    m = 2000000
    datadir = "run_data"
    datafile = datadir + os.path.sep + "alldata.dat"
    open(datafile, "w").close() # clobber the data file
    for ((dt, size), it) in itertools.product(dtypes, itypes):
        while n*size < 2**31:
            cmd = 'numactl -C 6 ./main {} {} {} {} >> {}'.format(dt, it, int(n), m, datafile)
            print cmd
            os.system(cmd)
            n *= base
    
        
