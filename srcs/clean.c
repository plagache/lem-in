/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:27:29 by plagache          #+#    #+#             */
/*   Updated: 2020/05/07 18:09:49 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	free_file(char **arr, char *str)
{
	free(str);
	free_arr((void**)arr);
}

void	free_list(t_list *lst)
{
	if (lst->next != NULL)
		free_list(lst->next);
	lst->content = NULL;
	free(lst);
}

void	free_graph(t_list *head, int code)
{
	t_room	*room;

	if (head != NULL)
	{
		if (head->next != NULL)
			free_graph(head->next, code);
		room = (t_room*)head->content;
		if ((code & 1) != 0 && room->neighbours != NULL)
			free_list(room->neighbours);
		if ((code & 2) != 0 && room->room_name != NULL)
			free(room->room_name);
		free(room);
		free(head);
	}
}

void	free_matrice(char **matrice, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(matrice[i]);
	free(matrice);
}

void	free_paths(t_path *paths, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		free_list((paths + i)->list);
	}
	free(paths);
}
