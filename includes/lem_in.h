/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:45:44 by alagache          #+#    #+#             */
/*   Updated: 2020/05/07 17:33:32 by plagache         ###   ########.fr       */
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
# define FAILURE -42
# define BUFF_SIZE 4096
# define END_COMMAND 64
# define START_COMMAND 1
# define MALLOC_FAILURE -1
# define NO_ROOM 2
# define NEW_PATH -2
# define NO_PATH -3
# define LIST_FAIL -1
# define PATH_FAIL -2
# define DEBUG -9876
# define PRINT_LN 1

typedef struct	s_path
{
	t_list		*list;
	int			len;
	int			ants;
	int			out;
	int			in;
}				t_path;

typedef struct	s_path_container
{
	t_path	*paths;
	int		flow;
	int		turns;
}				t_path_cont;

typedef struct	s_lem_in
{
	char		**file_split;
	char		**m_flow;
	char		*file;
	t_path_cont	best_paths;
	t_path		*paths;
	t_list		*head;
	t_list		*start_ptr;
	t_list		*end_ptr;
	int			nbr_ants;
	int			line;
	int			line_ants;
	int			rooms;
	int			options;
}				t_lem_in;

typedef	struct s_room	t_room;

struct			s_room
{
	char	*room_name;
	t_room	*parent;
	t_room	*next_front;
	t_list	*neighbours;
	int		level;
	int		flow;
	int		in_path;
	char	visited;
	char	command;
	int		ant_id;
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

int				edmond_karp(t_lem_in *lem_in);

/*
** Read
*/

int				read_file(t_lem_in *info);
int				split_file(t_lem_in *info);

/*
** Get_ info
*/

int				get_ants(t_lem_in *info);
int				get_rooms(t_lem_in *info);
int				get_commands(t_lem_in *info);
int				get_links(t_lem_in *info);
int				mv_to_next_room(t_lem_in *info);
void			sort_function(t_list *head);
int				validate_data(t_lem_in *info);
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
int				option_check(int ac, char **av, t_lem_in *info);

/*
** Clean
*/

void			free_list(t_list *lst);
void			free_file(char **arr, char *str);
void			free_graph(t_list *head, int code);
void			free_matrice(char **matrice, int size);
void			free_paths(t_path *paths, int size);

/*
** Print
*/

void			print_farm(char **arr);
int				display_list(t_list *info);
int				display_data(t_lem_in *info);
int				print_neighbours(t_room *room);
void			print_roomnames(t_room *room);
int				display_paths(t_path *paths, int flow);

/*
** Algorithme
*/

int				breadth_first_search(t_list *start_ptr, t_lem_in *info);

/*
** Path
*/

int				path(t_lem_in *lem_in, int *flow);
int				path_len(t_list *path);
t_path			*create_path_array(int flow);
int				check_collision(t_path **paths, int *flow);
void			sort_paths(t_path *paths, int flow);
void			split_ants(int ants, int flow, t_path *paths);
int8_t			move_paths(int flow, t_path *paths);
void			update_best_paths(t_path_cont *best, t_path_cont *new);

#endif
