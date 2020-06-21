#dont forget about  -Wall -Wextra -Werror 
NAME = npuzzle
CC = gcc
SRC := $(wildcard src/*.c)
SRO := $(notdir $(patsubst %.c, %.o, $(SRC)))
SRH := $(wildcard includes/*.h)
VPATH := src includes

all: $(NAME)

$(NAME): $(SRO) $(SRH)
	$(CC) $(SRO) -o $(NAME) -lm

%.o : %.c
	$(CC) -g -c -I ./includes/ $<

clean:
	/bin/rm -f $(SRO)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all