.POSIX:
.SUFFIXES:

CC = clang
# CPPFLAGS = -D_POSIX_C_SOURCE=200809L
CFLAGS   = -std=c11 -Wall -Wextra -Wpedantic -O3

all: tree-test

linked_list_generic.o: linked_list_generic.c linked_list_generic.h
tree.o: tree.c tree.h

tree-test: linked_list_generic.o linked_list_generic.h tree.o tree.h
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) linked_list_generic.o tree.o $(LDLIBS)

Josephine Maya Simple (she/they) (SP2'22): my internet cut out

clean:
	rm -f tree-test linked_list_generic.o tree.o

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

