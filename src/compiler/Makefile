ifneq ($V,1)
Q ?= @
endif

DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = 

UTILS_SRC = utils/error.c \
	  utils/link_node.c \
	  utils/link_list.c \
	  utils/symbol_table.c \
	  utils/parsing_tree.c \

SRC = lexical.c \
	  parser.c \
	  byte_code.c \
	  compiler.c

UTILS_OBJ = $(UTILS_SRC:.c=.o)

OBJ	=	$(SRC:.c=.o)

BINS	=	compiler

all: compiler

debug: CFLAGS += -DDEBUG -g
debug: compiler

test: CFLAGS += -DXTEST -DDEBUG -g
test: unittest

compiler: $(UTILS_OBJ) $(OBJ)
	$Q echo [linking compiler]
	$Q $(CC) -o $@ $(UTILS_OBJ) $(OBJ) $(LDFLAGS) $(LDLIBS)

unittest: lexical.o parser.o byte_code.o $(UTILS_OBJ)
	$Q echo [build unittest]
	$Q $(CC) -o test_lexical lexical.o $(UTILS_OBJ) $(LDFLAGS) $(LDLIBS)
	$Q $(CC) -o test_parser parser.o $(UTILS_OBJ) $(LDFLAGS) $(LDLIBS)
	$Q $(CC) -o test_bytecode byte_code.o $(UTILS_OBJ) $(LDFLAGS) $(LDLIBS)

test_link_node: CFLAGS += -DLINK_NODE_TEST -DDEBUG -g
test_link_node: ./utils/error.o ./utils/link_node.o
	$Q $(CC) -o $@ ./utils/link_node.o ./utils/error.o $(LDFLAGS) $(LDLIBS)

test_link_list: CFLAGS += -DLINK_LIST_TEST -DDEBUG -g
test_link_list: ./utils/error.o ./utils/link_node.o ./utils/link_list.o
	$Q $(CC) -o $@ ./utils/link_list.o ./utils/link_node.o ./utils/error.o $(LDFLAGS) $(LDLIBS)

test_symbol_table: CFLAGS += -DSYMBOL_TABLE_TEST -DDEBUG -g
test_symbol_table: ./utils/error.o ./utils/symbol_table.o 
	$Q $(CC) -o $@ ./utils/error.o ./utils/symbol_table.o $(LDFLAGS) $(LDLIBS)

test_parsing_tree: CFLAGS += -DPARSING_TREE_TEST -DDEBUG -g
test_parsing_tree: ./utils/error.o ./utils/parsing_tree.o
	$Q $(CC) -o $@ ./utils/error.o ./utils/parsing_tree.o $(LDFLAGS) $(LDLIBS)

.c.o:
	$Q echo [CC] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) $(UTILS_OBJ) *~ core tags $(BINS) test_*

tags:	$(SRC)
	$Q echo [ctags]
	$Q ctags $(SRC)

depend:
	makedepend -Y $(SRC)