# In The Name Of God
# ========================================
# [] File Name : Makefile
#
# [] Creation Date : 10-03-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================

P=kurskal
OBJ=kurskal.o edge.o diset.o main.o
LIB=
MLIB=

ifdef LIB
CFLAGS=-Wall -O0 -g -std=gnu11 \
       $(shell pkg-config --cflags $(LIB))
LDLIBS=$(shell pkg-config --libs $(LIB)) $(MLIB)
else
CFLAGS=-Wall -O0 -g -std=gnu11
LDLIBS=$(MLIB)
endif
ASFLAGS=-Wall -O0 -g

$(P): $(OBJ)
	$(CC) -o $(P) $(OBJ) $(LDLIBS)
main.o:
diset.o: diset.h
edge.o: edge.h
kurskal.o: edge.h diset.h

.PHONY: clean
clean:
	rm $(OBJ) $(P)
