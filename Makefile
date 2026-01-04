TARGET = main
OBJ = main.c parser.c execute.c utils.c
CFLAGS = -Wall -Wextra -Werror
CC = gcc

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
clean:
	rm -f *-o 
fclean: clean
	rm -f $(TARGET)
re: fclean all
