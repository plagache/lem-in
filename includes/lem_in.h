#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h> 
# include <unistd.h> 
# include <string.h> 
# include <stdio.h> 
# include "libft.h"

# define SUCCESS 0
# define FAILURE 1
# define BUFF_SIZE 100
# define STRNEW_FAILURE -1
# define STRJOIN_FAILURE -2
typedef struct	s_lem_in
{
	char		*file;
	t_list		*head;
}				t_lem_in;

# endif
