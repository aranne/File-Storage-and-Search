IDIR = ../h
INCLUDE = -I${IDIR}
CFLAGS  = -m32 -march=i586 -fno-builtin -Wall -O0 ${DEFS} ${INCLUDE}

CC = gcc
LIBS = -lm

SRC = main.c load.c Array.c mem_lin.c mem_bin.c lin_search.c bin_search.c 


_DEPS = $(wildcard ../h/*.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = ${SRC:%.c=%.o}
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

${ODIR}/%.o:../src/%.c ${DEFS}
	${CC} -c $< -o $@ ${CFLAGS}

PDIR = ..

_TARGET = assn_1
TARGET = ${PDIR}/${_TARGET}

${TARGET}:${OBJ}
	${CC} -o $@ ${OBJ} ${CFLAGS} ${LIBS}

ARGS = ${PDIR}/key.db ${PDIR}/seek.db

_OUTPUT = test.txt
OUTPUT = ${PDIR}/${_OUTPUT} 
run: ${TARGET}
	./${TARGET} ${ARGS} > ${OUTPUT}


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TARGET) ${OUTPUT}