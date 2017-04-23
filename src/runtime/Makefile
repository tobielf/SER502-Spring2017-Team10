ifneq ($V,1)
Q ?= @
endif

DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = 

SRC = runtime.c \
	  instruction.c \
	  storage.c

OBJ	=	$(SRC:.c=.o)

BINS	=	runtime

all: runtime

debug: CFLAGS += -DXTEST -DDEBUG -g
debug: unittest

runtime: $(OBJ) runtime.o
	$Q echo [linking runtime]
	$Q $(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

unittest: instruction.o storage.o runtime.o
	$Q echo [build unittest]
	$Q $(CC) -o test_runtime $(OBJ) $(LDFLAGS) $(LDLIBS)

.c.o:
	$Q echo [CC] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) *~ core tags $(BINS) test_*

tags:	$(SRC)
	$Q echo [ctags]
	$Q ctags $(SRC)

depend:
	makedepend -Y $(SRC)