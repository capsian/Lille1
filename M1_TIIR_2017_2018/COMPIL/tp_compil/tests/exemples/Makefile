# Utiliser quelque chose comme « make BINDIR=$HOME/compil/ » si jsp
# n’est pas dans le PATH

SOURCES := $(wildcard *.js)
PARSABLES := $(filter-out $(wildcard *-lo.js), $(SOURCES))

all: $(patsubst %.js,%.lex,$(SOURCES))
all: $(patsubst %.js,%.unlex,$(SOURCES))
all: $(patsubst %.js,%.pars,$(PARSABLES))
all: $(patsubst %.js,%.unpars,$(PARSABLES))

%.lex: %.js
	$(BINDIR)jsp -n   $< -o $@

%.unlex: %.lex
	$(BINDIR)jsp -lnt $< -o $@

%.pars: %.lex
	$(BINDIR)jsp -l   $< -o $@

%.unpars: %.pars
	$(BINDIR)jsp -pt  $< -o $@

clean:
	rm -rf *.unlex *.unpars

realclean: clean
	rm -rf *.lex *.pars

.PHONY: all clean realclean
