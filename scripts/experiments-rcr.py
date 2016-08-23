import os
import sys
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

def get_free_ram():
    try:
        output = subprocess.check_output('free').decode("utf-8")
        for line in output.splitlines():
            m = re.match(r'Mem:\s+\d+\s+\d+\s+(\d+)', line)
            if m:
                return int(m.group(1))
    except OSError:
        pass
    sys.err.write("Warning: Unable to determine available RAM, using 1GB\n")
    return 2**30
   
if __name__ == "__main__":
    ram = get_free_ram()
    N = min(ram//3, 5*2**30)
    print("Detected {} bytes of free RAM, using {} bytes".format(ram, 2*N))
    base = 1.258925412
    itypes = ["uint64"]
    datadir = "data-rcr"

    cpu = get_cpu_number()
    print("Pinning to CPU {}".format(cpu))

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

