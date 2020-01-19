IDIR = ../h
INCLUDE = -I${IDIR}
CFLAGS  = -m32 -march=i586 -fno-builtin -Wall -O0 ${DEFS} ${INCLUDE}

CC = gcc
LIBS = -lm

SRC = main.c load.c


_DEPS = $(wildcard ../h/*.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = ${SRC:%.c=%.o}
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

${ODIR}/%.o:../src/%.c ${DEFS}
	${CC} -c $< -o $@ ${CFLAGS}

TARGET = assn_1
PDIR = ..
${PDIR}/${TARGET}:${OBJ}
	${CC} -o $@ ${OBJ} ${CFLAGS} ${LIBS}

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o ${PDIR}/$(TARGET)


ARGS = key.db
run: ${PDIR}/${TARGET}
	./${PDIR}/${TARGET} ./${PDIR}/${ARGS}

