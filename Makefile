# Name of the project
PROJECT = main.o
 
# .h files
#H_SOURCE = $(wildcard ./src/*.h)

# Directories
DIR_SRC += .
DIR_SRC = ./src
DIR_INC += $(addprefix -I, $(DIR_SRC))

# .c files
C_SOURCE += $(wildcard $(addsuffix /*.c, $(DIR_SRC)))

# Object files
OBJ := $(patsubst %.c, %.o, $(C_SOURCE))

# Executable
EXE := obj/$(PROJECT)
 
# Compiler and linker
CC = gcc
 
# Flags for compiler
#CC_FLAGS = -c         \
#					 -Wall       \
#					 -ansi       \
#					 -pedantic
 
# Command used at clean target
RM = rm -rf
 
#
# Compilation and linking
#
.PHONY:all

all:$(OBJ) $(EXE)

%.o: %.c
	@ echo 'Building target using GCC compiler:$@'
	$(CC) $(DIR_INC) -c $< -o $@
	@ echo ' '

$(EXE): $(OBJ)
	@ echo 'Building binary using GCC linker: $<'
	$(CC) $(OBJ) -o $@ $(DIR_INC)
	@ echo 'Finished building binary: $@'
	@ echo ' '

	@ echo 'Removing remaining objects...'
	$(RM) $(DIR_SRC)/*.o
	@ echo 'Done!'
	@ echo ' '

	printf "\033c"
	sh run.sh

clean:
	rm -r *.o
