# In The Name Of God
# ========================================
# [] File Name : Makefile
#
# [] Creation Date : 08-04-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================

P=fknapsack
OBJ=fknapsack.o main.o object.o
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
main.o: object.h fknapsack.h
object.o: object.h
fnapsack.o: fnapsack.h object.h

.PHONY: clean
clean:
	rm $(OBJ) $(P)
