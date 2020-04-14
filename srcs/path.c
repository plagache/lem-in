/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 14:16:19 by plagache          #+#    #+#             */
/*   Updated: 2020/04/14 15:12:12 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"
#include <stdio.h>

/*
** input
** get_path(matrice, start, neigh, t_list *path)
** 	procedure
** 	- add start to path
** 	- find next neigh with positive flow
**	- call again (neigh , neigh-neigh)
** output t_list*
** //&& ((t_room*)ptr->content)->in_path == 0)
*/

int		get_path(char **matrice, t_list *start, t_list *neigh, t_list **path)
{
	t_list *ptr;

	if (new_link(path, (t_room*)start->content) == FAILURE)
	{
		free_list(*path);
		return (FAILURE);
	}
	ptr = neigh;
	while (ptr != NULL)
	{
		if (matrice[((t_room*)start->content)->id][((t_room*)ptr->content)->id]
			== 1)
		{
			if (get_path(matrice, ptr, ((t_room*)ptr->content)->neighbours,
				path) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (SUCCESS);
}

/*
** takes a t_list ** and a flow matrice
** find the link between start and it s neighbours and remove flow between them
*/

void	remove_flow(t_list **path, char **matrice)
{
	t_list *ptr;

	ptr = *path;
	while (ptr->next != NULL && ((t_room*)(ptr->next)->content)->id != 0)
		ptr = ptr->next;
	matrice[((t_room*)ptr->content)->id][0] = 0;
	matrice[0][((t_room*)ptr->content)->id] = 0;
}

/*
** input matrice, arr of t_list *, start_ptr
** t_list neigh
** while i < flow
** call get_path(matrice, start, neigh)
** i++
** output fail or success
**			//clean(paths);
*/

int		add_paths(char **matrice, t_path *paths, t_list *start, int flow)
{
	t_list	*neigh;
	int		i;

	i = 0;
	neigh = ((t_room*)start->content)->neighbours;
	while (i < flow)
	{
		if (get_path(matrice, start, neigh, &((paths + i)->list)) == FAILURE)
		{
			return (FAILURE);
		}
		remove_flow(&((paths + i)->list), matrice);
		(paths + i)->len = path_len((paths + i)->list);
		i++;
	}
	return (SUCCESS);
}

void	re_add_flow(t_path *paths, int flow, char **matrice)
{
	t_list	*ptr;
	int		i;

	i = 0;
	while (i < flow)
	{
		ptr = (paths + i)->list;
		while (ptr->next != NULL && ((t_room*)(ptr->next)->content)->id != 0)
			ptr = ptr->next;
		matrice[((t_room*)ptr->content)->id][0] = -1;
		matrice[0][((t_room*)ptr->content)->id] = 1;
		i++;
	}
}

/*
** all printf in function
**
**	//dprintf(2, "collision flow is %i\n", new.flow);
**	//dprintf(1, "collision flow is %i\n", new.flow);
**	//display_paths(new.paths, new.flow);
**	//dprintf(1, "END OF PATH\n");
**	//dprintf(2, "END OF PATH\n");
**
**	//dprintf(2, "no collision flow is %i\n", new.flow);
**	//display_paths((lem_in->best_paths).paths, (lem_in->best_paths).flow);
**	//dprintf(2, "END OF PATH\n\n");
*/

int		path(t_lem_in *lem_in, int *flow)
{
	t_path_cont new;

	new.flow = *flow;
	new.paths = create_path_array(new.flow);
	if (new.paths == NULL)
		return (FAILURE);
	if (add_paths(lem_in->m_flow, new.paths, lem_in->start_ptr, new.flow)
		== FAILURE)
		return (FAILURE);
	re_add_flow(new.paths, new.flow, lem_in->m_flow);
	sort_paths(new.paths, new.flow);
	if (check_collision(&(new.paths), &(new.flow)) == FAILURE)
	{
		free_paths(new.paths, new.flow);
		return (FAILURE);
	}
	split_ants(lem_in->nbr_ants, new.flow, new.paths);
	new.turns = (new.paths)[0].len + (new.paths)[0].ants;
	update_best_paths(&(lem_in->best_paths), &new);
	return (SUCCESS);
}
