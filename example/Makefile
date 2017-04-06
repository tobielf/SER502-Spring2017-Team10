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

BINS	=	$(SRC:.c=)

main: $(OBJ)
	$Q echo [link]
	$Q $(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

.c.o:
	$Q echo [CC] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) *~ core tags $(BINS)

tags:	$(SRC)
	$Q echo [ctags]
	$Q ctags $(SRC)

depend:
	makedepend -Y $(SRC)
