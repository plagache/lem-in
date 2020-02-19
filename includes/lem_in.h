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
# define NO_ROOM 2

typedef struct	s_lem_in
{
	char		**file_split;
	char		*file;
	t_list		*head;
	t_list		*start_ptr;
	t_list		*end_ptr;
	long long	nbr_ants;
	int			line;
	int			line_ants;
}				t_lem_in;

typedef struct	s_room
{
	char		*room_name;
	t_list		*neighbours;
	int			empty;
	char		command;
}				t_room;

/*
** t_list:
** content t_roon
** next next_link
*/

/*
** 00000000
** bit 1 is start
** bit 128 is end
*/

int				master(t_lem_in *info);
int				get_ants(t_lem_in *info);
int				get_rooms(t_lem_in *info);
int				get_links(t_lem_in *info);
int				is_command(char *str);
int				is_comment(char *str);
int				is_room(char *str);
int				is_link(char *str);
int				occurrence_of(char *str, char c);
void			mv_to_next_room(t_lem_in *info);

# endif
