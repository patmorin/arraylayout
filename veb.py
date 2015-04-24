import sys

class Node(object):
    """Represents a node in a (complete) binary tree"""

    def __init__(self, left, right):
        self.left = left
        self.right = right
        self.iolabel = "X" 
        self.veblabel = "Y" 

    def label_in_order(self, i):
        """Label this subtree in-order, starting with label i
  
        Return the value of the largest label used.
        """
        if self.left:
            self.iolabel = self.left.label_in_order(i) + 1 
            j = self.right.label_in_order(self.iolabel+1) 
        else:
            self.iolabel = i
            j = self.iolabel
        return j


    def label_veb(self, h, i):
        """Label the subtree of height h rooted here using VEB numbering

        Start the labelling at i and return the value of the largest label
        used.
        """
        if h < 0: 
            raise ValueError()
        if h == 0:
            self.veblabel = i
            return i
        m = h//2

        t = self.label_veb(m, i) 
        assert(t == i+2**(m+1)-2)
        i = t

        for u in self.enum_descendants(m+1):
            i = u.label_veb(h-m-1, i+1)
        return i

    def enum_descendants(self, d):
        """Enumerate all descendants of self at depth d"""
        if d == 0: 
            yield self
            return
        for u in self.left.enum_descendants(d-1):
            yield u
        for u in self.right.enum_descendants(d-1):
            yield u


    def veb_to_array(self, a):
        if self.left:
            a[self.veblabel] = (2*self.iolabel,
                                self.left.veblabel-self.veblabel, 
                                self.right.veblabel-self.veblabel)
            self.left.veb_to_array(a)
            self.right.veb_to_array(a)
        else:
            a[self.veblabel] = (2*self.iolabel, -1, -1)

    def __str__(self):
        if self.left:
            return "({}{},{}{})".format(str(self.left),
                                        self.iolabel, 
                                        self.veblabel,
                                        str(self.right)) 
        else:
            return "({},{})".format(self.iolabel, self.veblabel) 

def build_binary_tree(h):
    if h < 0:
        return None
    return Node(build_binary_tree(h-1), build_binary_tree(h-1))

def sequencer(h, s, d):
    if h == 0: return
    h0 = h//2
    h1 = h-h0-1 
    sequencer(h0, s, d)
    # (add, multiply, base depth, number of bits of p)
    s[d+h0] = (2**(h0+1)-1, 2**(h1+1)-1, d, h0+1)
    sequencer(h1, s, d+h0+1)

def try_it2(a, h, x):
    # The magic sequence
    s = [None]*(h+1)
    sequencer(h, s, 0)
    s[h] = (0, 0, h, 0)

    rtl = [None]*(h+1)   # the root to leaf path

    y = -1
    i = 0
    p = 0
    for d in range(h+1): 
        rtl[d] = i
        if x < a[i][0]:
            print "{} < {}".format(x, a[i][0])
            p = p*2
            y = a[i][0]
        elif x > a[i][0]:
            print "{} > {}".format(x, a[i][0])
            p = p*2+1
        else:
            print "{} = {} done".format(x, a[i][0])
            return a[i][0]
        
        m = (1 << s[d][3])-1
        i = rtl[s[d][2]] + s[d][0] + (p&m)*s[d][1]
    return y
             
def try_it(a, h, i, x):
    #print "i={} h={} x={}".format(i, h, x)
    if h == 0:
        if x < a[i][0]:
            print "{} < {}".format(x, a[i][0])
            return 0
        elif x > a[i][0]:
            print "{} > {}".format(x, a[i][0])
            return 1
        else:
            print "{} = {} done".format(x, a[i][0])
            return 0
    m = h // 2

    # we now have the high-order bits on this path
    r = try_it(a, m, i, x)

    #print "i0={}".format(i)
    i += 2**(m+1)-1
    #s = 2**(m+1)-1
    #print "i1={}".format(i)

    h = h-m-1

    i += r * (2**(h+1)-1)
    #t = (2**(h+1)-1)
    #print "i2={}".format(i)

    #print "+{} *{}".format(s, t)

    r = r * 2**(m+1) + try_it(a, h, i, x)
    return r
     

if __name__ == "__main__":
    
    if len(sys.argv) == 1:
        h = 4
    elif len(sys.argv) == 2:
        h = int(sys.argv[1])
    else:
        sys.err.writeln("Usage: {} [height]".format(h))
        sys.exit(-1)
     
    n = 2**(h+1)-1
    print "{} {}".format(h, n)
    t = build_binary_tree(h)
    t.label_in_order(0)
    t.label_veb(h, 0)
    a = [None]*n
    t.veb_to_array(a)
    a = [(a[i][0], a[i][1]+i, a[i][2]+i) for i in range(len(a))]
    print a
    try_it(a, h, 0, 127)
    try_it2(a, h, 127)
    print "===="
    aa = [None]*(h+1)
    sequencer(h, aa, 0)
    print aa

    



