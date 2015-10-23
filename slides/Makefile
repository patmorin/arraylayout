


slides.pdf : slides.tex figs/
	(cd figs; make)
	latexmk -pdf -e '$$pdflatex=q/pdflatex %O -shell-escape %S/' slides.tex	
