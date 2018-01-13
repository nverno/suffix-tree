ROOT    = $(shell echo ~/src/emacs)
CC      = gcc
CFLAGS  = -ggdb3 -Wall -std=c11
LDFLAGS =

all: suffix-tree.so

%.so: %.o
	$(LD) -shared $(LDFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -I$(ROOT)/src -fPIC -c $<
