##
## Makefile for corewar in /home/moutou_m/rendu/CPE/CPE_2015_corewar
##
## Made by moutou_m
## Login   <moutou_m@epitech.net>
##
## Started on  Thu Mar 24 21:51:38 2016 moutou_m
## Last update Thu Mar 24 21:51:38 2016 moutou_m
##

SRC	= $(shell find ./src -name '*.c')

NAME	= server

count	= 0
counter = $(shell find ./src -name '*.c' | wc -l)
ECHO	=	/bin/echo -e

CC	= gcc

CFLAGS	=	-W \
		-Wall \
		-Wextra \
		-Werror \
		-I./include/ \
		-g

LDFLAGS	=	

RM	= rm -f

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(LDFLAGS) $(OBJ)
	@echo

clean:
	@$(RM) $(OBJ)
	@$(RM) *~

fclean: clean
	@$(RM) $(NAME)

re: fclean all

%.o: %.c
	$(eval count=$(shell $(ECHO) $$(($(count)+1))))
	@$(ECHO) -n "\r$(shell $(ECHO) "$(count) * 100 / $(counter)" | bc)% \033[1;34m$(NAME)\033[0m"
	@$(CC) -o $@ -c $< $(CFLAGS)
