CFLAGS = -std=c99 -g -O3 -Wall -Wextra -Werror
OBJ = items.o characters.o rooms.o adventure.o 
PROG = game

$(PROG): $(OBJ)
		gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)