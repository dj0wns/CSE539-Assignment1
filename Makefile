COMPILER=gcc
ARGS=-Wall -O3
OUTFILE=bin/crypto
SRCDIR=src
OBJDIR=obj

all: $(OUTFILE)

clean:
	rm $(OBJDIR)/* $(OUTFILE)

$(OUTFILE): $(OBJDIR)/main.o
	$(COMPILER) $(ARGS) -o $(OUTFILE) $(OBJDIR)/*.o

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	$(COMPILER) $(ARGS) -c -o $(OBJDIR)/main.o $(SRCDIR)/main.c
