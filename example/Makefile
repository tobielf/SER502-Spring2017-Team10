ifneq ($V,1)
Q ?= @
endif

DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = 

SRC = main.c \
      error.c \
	  init.c \
	  symbol.c \
	  emitter.c \
	  parser.c \
	  lexer.c

OBJ	=	$(SRC:.c=.o)

BINS	=	compiler \
			runtime

all: compiler runtime

compiler: $(OBJ)
	$Q echo [linking compiler]
	$Q $(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

runtime: runtime.o
	$Q echo [linking runtime]
	$Q $(CC) -o $@ runtime.o $(LDFLAGS) $(LDLIBS)

.c.o:
	$Q echo [CC] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) *~ core tags $(BINS)
	$Q rm -f runtime.o

tags:	$(SRC)
	$Q echo [ctags]
	$Q ctags $(SRC)

depend:
	makedepend -Y $(SRC)
