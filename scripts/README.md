These are the scripts used to make figures in the paper as well as the scripts
for the JEA RCR certification.

experiments.py: runs a sequence of experiments and saves the data in
                the run_data/ directory

snarf.py:       makes PDF figures in the figs/ directory using data from the
                data/ directory

data/           contains data from experiments that are used in the paper

experiments-rcr.py: runs experiments and puts data in the data-rcr directory
                    (used by ../rcr script)

snarf-rcr.py:       uses data in data-rcr/ to make figures in figs-rcr
                    (used by ../rcr script)

snarf-slides.py:    makes figures for a talk I once gave
