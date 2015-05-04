import os

def load_data(name):
    filename = "{}{}{}.data".format("run_data", os.path.sep, name)
    lines = open(filename).read().splitlines()
    result = [ line.strip('s').split() for line in lines ]
    result = dict(result)
    return result

if __name__ == "__main__":
    fake = load_data("fake")
    binary = load_data("binary")
    ks = [ int(k) for k in fake.keys() ]
    ks.sort()
    ks = [ str(k) for k in ks ]
    for alg in ["17-tree", "veb", "binary", "eytzinger"]:
        data = load_data(alg)
        ofilename = "{}{}{}-rel.data".format("run_data", os.path.sep, alg)
        of = open(ofilename, "w");
        for k in ks:
            of.write("{} {}\n".format(k, (float(binary[k])-float(fake[k])) 
                                         / (float(data[k])-float(fake[k]))))
