IDIR=headers
SDIR=src
ODIR=$(SDIR)/obj
# LDIR =lib
# LIBS=-lm -lncurses

CC=gcc
CFLAGS=-I$(IDIR)


_DEPS = all.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o prompt.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

ssh: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	@echo '**************************************************'
# can use below if lib required
# $(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
