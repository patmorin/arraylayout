"""Check the correctness of our arraylayout implementations"""
from __future__ import division
import subprocess
import itertools
import sys
from math import log

dtypes=['uint32', 'uint64', 'uint128']
itypes=['uint32', 'uint64']
b = 10**(1/10)
ns = list(range(1, 1000))
ns += [int(1000+b**i) for i in range(int(log(10**7, b)))]
tick = len(dtypes)*len(itypes)*len(ns) // 70
errors = 0
count = 0
newerr = False
for (dt, it, n) in itertools.product(dtypes, itypes, ns):
    count += 1
    if newerr or count % tick == 0:
        sys.stdout.write("\r" + ("="*(count//tick)))
        sys.stdout.flush()
        newerr = False
    out = subprocess.check_output(['./main', dt, it, str(n), str(min(10*6, n*5))])
    d = dict()
    for line in out.splitlines():
        line = line.split()
        if line:
            d[line[0]] = line[-1]
    values = [d[x] for x in d]
    correct = sorted(values)[len(values)//2]
    for x in d:
        if d[x] != correct:
            if not newerr:
                newerr = True
                sys.stdout.write("\r")
            errors += 1
            print("Warning: {} {} {} {} = {} (correct = {})".format(dt, it, n, x, d[x], correct))

print("\nFinished with {} incorrect results".format(errors))
