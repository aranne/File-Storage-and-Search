IDIR = ../h
INCLUDE = -I${IDIR}
CFLAGS  = -Wall ${INCLUDE}

CC = gcc
LIBS = -lm

SRC = app.c btree_node.c btree.c test.c node.c queue.c 
	  


_DEPS = $(wildcard ../h/*.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = ${SRC:%.c=%.o}
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

${ODIR}/%.o:../src/%.c ${DEPS}
	${CC} -c $< -o $@ ${CFLAGS}

PDIR = ..

_TARGET = assn_4
TARGET = ${PDIR}/${_TARGET}

${TARGET}:${OBJ}
	${CC} -o $@ ${OBJ} ${CFLAGS} ${LIBS}

ARGS = ${PDIR}/input.bin 4

run: ${TARGET}
	./${TARGET} ${ARGS} < ${PDIR}/input-01-ex.txt > ${PDIR}/output-01-ex.txt

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TARGET) ${PDIR}/input.bin