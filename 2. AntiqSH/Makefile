IDIR=headers
SDIR=src
ODIR=$(SDIR)/obj
# LDIR =lib
# LIBS=-lm -lncurses

CC=gcc
CFLAGS=-I$(IDIR)


_DEPS = all.h my_command.h proc.h misc.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = \
	main.o path_utils.o prompt.o procs.o \
	handle_input.o handle_io.o handle_my_command.o handle_command.o handle_child.o \
	pipe.o \
	cd.o pwd.o echo.o repeat.o pinfo.o ls.o jobs.o fg.o bg.o sig.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

antiqsh: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	@echo '**************************************************'
# can use below if lib required
# $(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
