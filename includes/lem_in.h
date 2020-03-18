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
# define BUFF_SIZE 4096
# define END_COMMAND 64
# define START_COMMAND 1
# define STRNEW_FAILURE -1
# define STRJOIN_FAILURE -2
# define NO_ROOM 2
# define NEW_PATH -2
# define NO_PATH -3
# define LIST_FAIL -1
# define PATH_FAIL -2
# define DEBUG -9876

typedef struct	s_lem_in
{
	char		**file_split;
	char		**m_flow;
	char		*file;
	t_list		**paths;
	t_list		*head;
	t_list		*start_ptr;
	t_list		*end_ptr;
	long long	nbr_ants;
	int			line;
	int			line_ants;
	int			rooms;
}				t_lem_in;

typedef struct	s_room t_room;

struct			s_room
{
	char	*room_name;
	t_room	*parent;
	t_list	*neighbours;
	int		level;
	char	visited;
	char	command;
	int		id;
};

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
int				edmond_karp(t_lem_in *lem_in);

/*
** Read
*/


int				read_file(t_lem_in *);
int				split_file(t_lem_in *);

/*
** Get_ info
*/

int				get_ants(t_lem_in *info);
int				get_rooms(t_lem_in *info);
int				get_commands(t_lem_in *info);
int				get_links(t_lem_in *info);
int				mv_to_next_room(t_lem_in *info);
void			sort_function(t_list *head);
char			**create_matrice(t_lem_in *lem_in);

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
** Clean
*/

void			free_list(t_list *lst);
void			free_graph(t_list *head);
void			free_matrice(char **matrice, int size);
void			free_paths(t_list **paths, int size);

/*
** Print
*/

int				display_list(t_list *);
int				display_data(t_lem_in *info);
int				print_neighbours(t_room *room);
void			print_roomnames(t_room *room);
int				display_paths(t_lem_in *lem_in, int flow);

/*
** Algorithme
*/

int				breadth_first_search(t_list *, t_lem_in *);

/*
** Path
*/

int				path(t_lem_in *lem_in, int flow);

#endif
