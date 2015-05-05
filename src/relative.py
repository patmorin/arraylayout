import os


def load_data(datadir, name, op):
    filename = "{}{}{}-{}.data".format("run_data", os.path.sep, name, op)
    lines = open(filename).read().splitlines()
    result = [ line.strip('s').split() for line in lines ]
    result = dict(result)
    return result

if __name__ == "__main__":
    datadir = "run_data"
    op = "search"
    fake = load_data(datadir, "fake", op)
    binary = load_data(datadir, "binary", op)
    ks = [ int(k) for k in fake.keys() ]
    ks.sort()
    ks = [ str(k) for k in ks ]
    for alg in ["17-tree", "veb", "binary", "eytzinger"]:
        data = load_data(datadir, alg, op)
        ofilename = "{}{}{}-{}-rel.data".format(datadir, os.path.sep, alg, op)
        of = open(ofilename, "w");
        for k in ks:
            of.write("{} {}\n".format(k, (float(binary[k])-float(fake[k])) 
                                         / (float(data[k])-float(fake[k]))))
