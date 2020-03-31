IDIR = ../h
INCLUDE = -I${IDIR}
CFLAGS  = -Wall ${INCLUDE}

CC = gcc
LIBS = -lm

SRC = main.c buffer.c mergesort.c heap.c time_sub.c 
	  


_DEPS = $(wildcard ../h/*.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = ${SRC:%.c=%.o}
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

${ODIR}/%.o:../src/%.c ${DEPS}
	${CC} -c $< -o $@ ${CFLAGS}

PDIR = ..

_TARGET = assn_3
TARGET = ${PDIR}/${_TARGET}

${TARGET}:${OBJ}
	${CC} -o $@ ${OBJ} ${CFLAGS} ${LIBS}

ARGS = --replacement ${PDIR}/input.bin ${PDIR}/sort.bin

run: ${TARGET}
	./${TARGET} ${ARGS}

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TARGET) ${PDIR}/sort.bin ${PDIR}/input.bin.*