TARGET = main
SRC = main.c parser.c execute.c utils.c
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
