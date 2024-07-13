CC = gcc
CFLAGS = -Wall -fPIC


LIB_FILES = src/common.c src/forest.c src/linkedlist.c src/treeprinter.c
LIB_OBJS = common.o forest.o linkedlist.o treeprinter.o


main: $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ main.c -o $@
	@echo Execute the program using ./$@

$(LIB_OBJS): $(LIB_FILES)
	$(CC) $(CFLAGS) $^ -c

clean:
	-rm $(LIB_OBJS) main
