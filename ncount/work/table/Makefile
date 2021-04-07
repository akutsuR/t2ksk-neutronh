#LATEXMK = latexmk
LATEXMK = /usr/local/texlive/2020/bin/x86_64-linux/latexmk
LATEXMKOPT = -pdf -f

MAIN = t2ksk_nmeas_2019May
SOURCES = $(shell find ./*.tex -type f)
FIGURES = $(shell find ./plots/* -type f)

all: $(MAIN).pdf
	 $(RM) *.log *.out *.nav *.fls *.fdb_latexmk *.snm *.toc

$(MAIN).pdf: $(MAIN).tex Makefile $(SOURCES) $(FIGURES)
	$(LATEXMK) $(LATEXMKOPT) $<
	$(RM) *.aux

# Remove all temporary files
clean:
	$(LATEXMK) -c

# Remove all temporary files AND the output pdf
purge:
	$(LATEXMK) -CA

.PHONY: all clean purge
