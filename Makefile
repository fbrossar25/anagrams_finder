TARGET = search_anagrams
CC = gcc
CFLAGS = -Wall -o2 -std=c99 -O -g -I include
LDFLAGS = 
SRC = main string_op wildcard word_array word_dict

OBJ := $(addsuffix .o, $(addprefix obj/, $(SRC)))
SRC := $(addsuffix .c, $(addprefix src/, $(SRC)))

all: ${TARGET}

${TARGET}: dir ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

obj/%.o: src/%.c
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	rm -rf obj/

mrproper: clean
	rm -f ${TARGET}

dir :
	@if [ ! -d obj/ ]; then mkdir obj/; fi

remake: mrproper all