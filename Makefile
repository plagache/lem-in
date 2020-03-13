NAME = lem-in

SRC = lem_in.c \
	  parse.c \
	  read.c \
	  tools.c \
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
	#  validate_parsing.c\

SRCS = $(addprefix srcs/,$(SRCS))

OBJECT = $(addprefix out/,$(SRC:.c=.o))

LIBDIR = libft

LIBA = $(LIBDIR)/libft.a

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g3

CC = clang

all: $(NAME)

$(NAME): $(OBJECT)
	make -s -C $(LIBDIR)
	$(CC) $(CFLAGS) -I includes -I libft/includes -o $(NAME) $(OBJECT) $(LIBA)

FORCE:

out/%.o: srcs/%.c
	mkdir -p out
	$(CC) $(CFLAGS) -I includes -I libft/includes -o $@ -c $<

clean:
	$(RM) -rf out
	make -s -C $(LIBDIR) clean

fclean:
	$(RM) -rf out $(NAME)
	make -s -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re FORCE
.SILENT: fclean clean re
