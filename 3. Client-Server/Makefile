IDIR=headers
SDIR=src
ODIR=$(SDIR)/obj
# LDIR =lib
# LIBS=-lm -lncurses

CC=g++
CFLAGS=-I$(IDIR)


_DEPS = all.h commands.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = server.o commands.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -g -pthread -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -pthread -o $@ $^ $(CFLAGS) $(LIBS)
	@echo '**************************************************'
# can use below if lib required
# $(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
