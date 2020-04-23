# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagache <alagache@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 17:56:28 by alagache          #+#    #+#              #
#    Updated: 2020/04/23 22:51:23 by alagache         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = lem_in.c \
	  read.c \
	  tools.c \
	  tools_2.c \
	  sort.c\
	  print.c\
	  matrice.c\
	  ant.c\
	  bfs.c\
	  command.c\
	  edmond_karp.c\
	  link.c\
	  room.c\
	  print_ants.c\
	  path.c\
	  path_2.c \
	  clean.c\
	  split_ants.c\
	  collision.c\
	  validate_parsing.c\

SRCS = $(addprefix srcs/,$(SRCS))

OBJECT = $(addprefix out/,$(SRC:.c=.o))

LIBDIR = libft

LIBA = $(LIBDIR)/libft.a

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address -fno-omit-frame-pointer

CC = clang
#CC = gcc

BLUE = "\\033[36m"
RED = "\\033[31m"
WHITE = "\\033[0m"
GREEN = "\\033[32m"
PURPLE = "\\033[35m"

LNECLR = "\\33[2K\\r"

all: $(NAME)

$(NAME): $(OBJECT)
	make -s -C $(LIBDIR)
	$(CC) $(CFLAGS) -I includes -I libft/includes -o $(NAME) $(OBJECT) $(LIBA)
	printf "$(LNECLR)$(GREEN)make lem-in done$(WHITE)\n"

out/%.o: srcs/%.c includes/lem_in.h 
	mkdir -p out
	printf "$(LNECLR)$(NAME): $<"
	$(CC) $(CFLAGS) -I includes -I libft/includes -o $@ -c $<

clean:
	$(RM) -rf out
	make -s -C $(LIBDIR) clean
	printf "$(PURPLE)clean lem-in done$(WHITE)\n"

fclean:
	$(RM) -rf out $(NAME)
	make -s -C $(LIBDIR) fclean
	printf "$(PURPLE)fclean lem-in done$(WHITE)\n"

re: fclean all

.PHONY: fclean clean re FORCE
.SILENT: fclean clean re FORCE $(NAME) $(OBJECT)
