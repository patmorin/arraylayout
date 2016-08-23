import matplotlib as mpl


mpl.use("pgf")
pgf_with_pdflatex = {
	"font.family": "serif",
    "font.size": 9,
    "text.usetex" : True,
    "pgf.rcfonts": False,
    "pgf.texsystem": "pdflatex",
    "pgf.preamble": [
         r"\usepackage[utf8]{inputenc}",
         r"\usepackage[T1]{fontenc}",
         r"\usepackage{kpfonts}",
         ]
}
mpl.rcParams.update(pgf_with_pdflatex)

import snarflib

snarflib.make_plots()
