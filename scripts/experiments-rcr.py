"""This code is intended to be called by the ../rcr script"""
from __future__ import division
import os
import sys
import subprocess
import re
import itertools

def get_cpu_number():
    """Use lscpu to get the last CPU number on NUMA node 0"""
    try:
        output = subprocess.check_output('lscpu').decode("utf-8")
        for line in output.splitlines():
            m = re.match(r'NUMA node0.*:\s*\d+-(\d+)', line)
            if m:
                return m.group(1)
    except OSError:
        pass
    sys.stderr.write("Warning: Unable to select CPU ID, using 0\n")
    return 0

def get_free_ram():
    """Use free -b to determine the amount of free RAM"""
    try:
        output = subprocess.check_output(['free', '-b']).decode("utf-8")
        lines = output.splitlines()
        m = re.match(r'\w+:' + '(\s+(\d+))'*6, lines[1])
        if m:
            return int(m.group(6))
    except OSError:
        pass
    sys.stderr.write("Warning: Unable to determine free RAM, using 1GB\n")
    return 10**9

def b2gb(n):
    return n/10**9


def run_batch(cpu, dtypes, itypes, nt, datafile, N):  
    """Run a big batch of experiments"""
    for ((dt, size), it) in itertools.product(dtypes, itypes):
        base = 10**(1/10)
        n = base 
        m = 2000000
        while n*size < N:
            if nt == 1:
                cmd = 'numactl -C {} ./main {} {} {} {} >> {}'
                cmd = cmd.format(cpu, dt, it, int(n), m, datafile)
            else:
                cmd = './main-mt {} {} {} {} {} >> {}'
                cmd = cmd.format(dt, it, int(n), m, nt, datafile)
            print cmd
            if os.system(cmd) != 0:
                errmsg = "Error while executing '{}': Aborting!\n".format(cmd)
                sys.stderr.write(errmsg)
                sys.exit(-1)
            while int(n*base) == int(n):
                n *= base
            n *= base


if __name__ == "__main__":
    """Run our experiments"""

    # Use two-thirds of available RAM, up to 5GB
    ram = get_free_ram()
    N = min(ram//3, 5*2**30)
    msg = "Detected {:.2g}GB of free RAM, using {:.2g}GB"
    print(msg.format(b2gb(ram), b2gb(2*N)))

    # For single-thread experiments, pin to a single CPU
    cpu = get_cpu_number()
    print("Pinning to CPU {}".format(cpu))

    # Always use 64 bit indices
    itypes = ["uint64"]

    # Put the data here
    datadir = "data-rcr"

    # Test with 32-, 64-, and 128-bit data
    dtypes = [("uint32", 4), ("uint64", 8), ("uint128", 16)]

    # Create and clobber the output file
    datafile = datadir + os.path.sep + "alldata.dat"
    open(datafile, "w").close()

    # Now do the real work
    run_batch(cpu, dtypes, itypes, 1, datafile, N)

    # Rerun the 32-bit tests using 2, 4, and 8 threads
    for nt in [2, 4, 8]:
        dtypes = [("uint32", 4)]
        datafile = datadir + os.path.sep + "alldata-mt-{}.dat".format(nt)
        open(datafile, "w").close() # clobber the data file
        run_batch(0, dtypes, itypes, nt, datafile, N)

