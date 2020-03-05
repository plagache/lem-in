/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:45:44 by alagache          #+#    #+#             */
/*   Updated: 2020/02/27 16:46:58 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define END_COMMAND 64
# define START_COMMAND 1
# define STRNEW_FAILURE -1
# define STRJOIN_FAILURE -2
# define NO_ROOM 2
# define NO_PATH -3
# define LIST_FAIL -1
# define PATH_FAIL -2

typedef struct	s_lem_in
{
	char		**file_split;
	char		*file;
	t_list		*path_list;
	t_list		*head;
	t_list		*start_ptr;
	t_list		*end_ptr;
	long long	nbr_ants;
	int			line;
	int			line_ants;
}				t_lem_in;

typedef struct	s_room
{
	char	*room_name;
	t_list	*parent;
	t_list	*neighbours;
	int		level;
	char	capacity;
	char	command;
}				t_room;

/*
** state use bits:
** 	- 1 st bit is capacity: 0 Empty || 1 Full
*/

/*
** command use bits:
** 00000000
** bit 1 is start
** bit 128 is end
*/

int				master(t_lem_in *);
int				max_flow(t_list **, t_list *, t_list *, t_list *);
int				create_path(t_list **, t_list *, t_list *, t_list *);

/*
** Get_ info
*/

int				get_ants(t_lem_in *info);
int				get_rooms(t_lem_in *info);
int				get_commands(t_lem_in *info);
int				get_links(t_lem_in *info);
int				mv_to_next_room(t_lem_in *info);
void			sort_function(t_list *head);

/*
** Tools
*/

t_list			*search_room(t_lem_in *info, char *room);
int				is_command(char *str);
int				is_comment(char *str);
int				is_room(char *str);
int				is_link(char *str);
void			free_arr(void **arr);
int				occurrence_of(char *str, char c);
int				new_link(t_list **head, t_room *room_ptr);

/*
** print
*/

int				display_list(t_list *);
int				display_data(t_lem_in *info);
int				print_neighbours(t_room *room);
void			print_roomnames(t_room *room);

#endif
