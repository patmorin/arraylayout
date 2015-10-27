


slides.pdf : slides.tex figs graphs
	(cd figs; make)
	latexmk -pdf -e '$$pdflatex=q/pdflatex %O -shell-escape %S/' slides.tex	

clean :
	rm -f slides.pdf
