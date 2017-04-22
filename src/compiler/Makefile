ifneq ($V,1)
Q ?= @
endif

DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = 

SRC = utils/error.c \
	  utils/link_node.c \
	  utils/link_list.c \
	  utils/symbol_table.c \
	  utils/parsing_tree.c \
	  lexical.c \
	  parser.c \
	  byte_code.c

OBJ	=	$(SRC:.c=.o)

BINS	=	compiler

all: compiler

debug: CFLAGS += -DXTEST -DDEBUG -g
debug: unittest

compiler: $(OBJ) compiler.o
	$Q echo [linking compiler]
	$Q $(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

unittest: lexical.o parser.o byte_code.o
	$Q echo [build unittest]
	$Q $(CC) -o test_lexical lexical.o $(LDFLAGS) $(LDLIBS)
	$Q $(CC) -o test_parser parser.o $(LDFLAGS) $(LDLIBS)
	$Q $(CC) -o test_bytecode byte_code.o $(LDFLAGS) $(LDLIBS)

test_link_node: CFLAGS += -DLINK_NODE_TEST -DDEBUG -g
test_link_node: ./utils/error.o ./utils/link_node.o
	$Q $(CC) -o test_link_node ./utils/link_node.o ./utils/error.o $(LDFLAGS) $(LDLIBS)

test_link_list: CFLAGS += -DLINK_LIST_TEST -DDEBUG -g
test_link_list: ./utils/error.o ./utils/link_node.o ./utils/link_list.o
	$Q $(CC) -o test_link_list ./utils/link_list.o ./utils/link_node.o ./utils/error.o $(LDFLAGS) $(LDLIBS)

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