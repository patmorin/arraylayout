import os


def load_data(datadir, alg, dtype, itype):
    filename = "{}{}{}-{}-{}.data".format("run_data", os.path.sep, alg,
                                       dtype, itype)
    lines = open(filename).read().splitlines()
    result = [ line.strip('s').split() for line in lines ]
    result = [ (r[0], r[3]) for r in result ]
    result = dict(result)
    return result

if __name__ == "__main__":
    datadir = "run_data"
    for dtype in ["uint32", "float32", "uint64", "float64", "int128"]:
      for itype in ["uint32", "uint64"]:
        fake = load_data(datadir, "fake", dtype, itype)
        binary = load_data(datadir, "binary", dtype, itype)
        ks = [str(k) for k in sorted([ int(k) for k in fake.keys() ])]
        for alg in ["btree", "veb", "binary", "eytzinger"]:
            data = load_data(datadir, alg, dtype, itype)
            ofilename = "{}{}{}-{}-{}-rel.data".format(datadir, os.path.sep, 
                                                       alg, dtype, itype)
            of = open(ofilename, "w");
            for k in ks:
                numerator = float(binary[k])-float(fake[k]) 
                denominator = float(data[k])-float(fake[k])
                of.write("{} {}\n".format(k, numerator/denominator))
            of.close()
