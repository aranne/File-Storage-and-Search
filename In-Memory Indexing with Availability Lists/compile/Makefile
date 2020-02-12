IDIR = ../h
INCLUDE = -I${IDIR}
CFLAGS  = -Wall ${INCLUDE}

CC = gcc
LIBS = -lm

SRC = main.c interface.c array.c test.c arraylist.c \
      primindex.c holelist.c data.c 


_DEPS = $(wildcard ../h/*.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = ${SRC:%.c=%.o}
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

${ODIR}/%.o:../src/%.c ${DEPS}
	${CC} -c $< -o $@ ${CFLAGS}

PDIR = ..

_TARGET = assn_2
TARGET = ${PDIR}/${_TARGET}

${TARGET}:${OBJ}
	${CC} -o $@ ${OBJ} ${CFLAGS} ${LIBS}

_INPUT = input-02.txt 
INPUT = ${PDIR}/${_INPUT}

_OUTPUT = output.txt
OUTPUT = ${PDIR}/${_OUTPUT} 

ARGS = --best-fit ${PDIR}/stu​dent.​db 

run: ${TARGET}
	./${TARGET} ${ARGS} < ${INPUT} > ${OUTPUT}


_BINARY = firstindex.bin bestindex.bin worstindex.bin \
          firstlist.bin  bestlist.bin  worstlist.bin  \

BINARY = ${PDIR}/${_BINARY}

_DB = stu​dent.​db
DB = ${PDIR}/${_DB}

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TARGET) ${OUTPUT} ${_BINARY} ${BINARY} ${DB}