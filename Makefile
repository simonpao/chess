CC=gcc
CFLAGS=-I$(IDIR)
IDIR=inc
ODIR=obj
SDIR=src

_DEPS = globals.h board.h move.h win.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o board.o move.o win.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o chess.out $^ $(CFLAGS) $(LIBS)