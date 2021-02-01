PROJECT := main.o

DIR_SRC += .
DIR_SRC = ./src

DIR_INC += $(addprefix -I, $(DIR_SRC))

CC = gcc
CLIB = -L .

SRC_C += $(wildcard $(addsuffix /*.c, $(DIR_SRC)))
OBJ := $(patsubst %.c, %.o, $(SRC_C))
EXE := obj/$(PROJECT)

.PHONY:all

all:$(OBJ) $(EXE)

%.o: %.c
	$(CC) $(DIR_INC) -c $< -o $@

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(DIR_INC)
	rm -r src/*.o
	printf "\033c"
	sh config.sh

clean:
	rm -r *.o
