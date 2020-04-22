# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagache <alagache@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 17:56:28 by alagache          #+#    #+#              #
#    Updated: 2020/04/22 16:01:48 by alagache         ###   ########.fr        #
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

all: $(NAME)

$(NAME): $(OBJECT)
	make -s -C $(LIBDIR)
	$(CC) $(CFLAGS) -I includes -I libft/includes -o $(NAME) $(OBJECT) $(LIBA)

out/%.o: srcs/%.c includes/lem_in.h 
	mkdir -p out
	$(CC) $(CFLAGS) -I includes -I libft/includes -o $@ -c $<

clean:
	$(RM) -rf out
	make -s -C $(LIBDIR) clean

fclean:
	$(RM) -rf out $(NAME)
	make -s -C $(LIBDIR) fclean

re: fclean all

.PHONY: fclean clean re FORCE
.SILENT: fclean clean re FORCE $(NAME) $(OBJECT)
