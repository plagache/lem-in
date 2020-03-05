NAME = lem-in

SRC = lem_in.c \
	  parse.c \
	  read.c \
	  tools.c \
	  sort.c\
	  print.c\
	  flow.c\
	  path.c\

SRCS = $(addprefix srcs/,$(SRCS))

OBJECT = $(addprefix out/,$(SRC:.c=.o))

LIBDIR = libft

LIBA = $(LIBDIR)/libft.a

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g

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
