import os
import subprocess
import re
import itertools

def get_cpu_number():
    try:
        output = subprocess.check_output('lscpu').decode("utf-8")
        for line in output.splitlines():
            m = re.match(r'^NUMA node0.*:\s*\d+-(\d+)', line)
            if m:
                return m.group(1)
    except OSError:
        pass
    sys.err.write("Warning: Unable to select CPU ID, using 0\n")
    return 0
    
if __name__ == "__main__":
    N = 5*2**30
    base = 1.258925412
    itypes = ["uint64"]
    datadir = "data-rcr"

    cpu = get_cpu_number()

    dtypes = [("uint32", 4), ("uint64", 8), ("uint128", 16)]
    datafile = datadir + os.path.sep + "alldata.dat"
    open(datafile, "w").close()  # clobber the data file
    for ((dt, size), it) in itertools.product(dtypes, itypes):
        n = base;
        m = 2000000
        while n*size < N:
            cmd = 'numactl -C {} ./main {} {} {} {} >> {}'
            cmd = cmd.format(cpu, dt, it, int(n), m, datafile)
            print cmd
            if os.system(cmd) != 0:
                sys.stderr.write("Error while executing '{}': Aborting!\n")
                sys.exit(-1)
            while int(n*base) == int(n):
                n *= base
            n *= base

    for nt in [2, 4, 8]:
        dtypes = [("uint32", 4)]
        datafile = datadir + os.path.sep + "alldata-mt-{}.dat".format(nt)
        open(datafile, "w").close() # clobber the data file
        for ((dt, size), it) in itertools.product(dtypes, itypes):
            n = base;
            m = 2000000
            while n*size < N:
                cmd = './main-mt {} {} {} {} {} >> {}'
                cmd = cmd.format(dt, it, int(n), m, nt, datafile)
                print cmd
                if os.system(cmd) != 0:
                    sys.stderr.write("Error while executing '{}': Aborting!\n")
                    sys.exit(-1)
                while int(n*base) == int(n):
                    n *= base
                n *= base

