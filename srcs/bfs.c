/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:26:33 by plagache          #+#    #+#             */
/*   Updated: 2020/04/14 13:26:52 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

/*
** input start
** output start or NULL if error
** visit all vertices with positive capacity
** check all neighbours in neigh_list
** add neigh to Q
*/

void	add_to_front(t_room *to_add, t_room **queue)
{
	to_add->next_front = *queue;
	*queue = to_add;
}

/*
** add neigh_ptr->content ROOM to the next_f queue
*/

int		set_levels(t_room *front_ptr, t_room **next_f, int levels,
					t_lem_in *lem_in)
{
	t_list	*neigh_ptr;

	neigh_ptr = front_ptr->neighbours;
	while (neigh_ptr != NULL)
	{
		if (((t_room*)(neigh_ptr->content))->level == 0
			&& lem_in->m_flow[front_ptr->id]
			[((t_room*)(neigh_ptr->content))->id] < 1)
		{
			if (front_ptr == lem_in->start_ptr->content
				|| !(front_ptr->parent->flow == 0 && front_ptr->flow == 1
				&& ((t_room*)(neigh_ptr->content))->flow == 0))
			{
				((t_room*)(neigh_ptr->content))->level = levels;
				((t_room*)(neigh_ptr->content))->parent = front_ptr;
				add_to_front((t_room*)(neigh_ptr->content), next_f);
				if (lem_in->end_ptr->content == neigh_ptr->content)
					return (NEW_PATH);
			}
		}
		neigh_ptr = neigh_ptr->next;
	}
	return (NO_PATH);
}

int		set_frontier(t_room *frontier, t_lem_in *lem_in, t_room **next_f,
					int levels)
{
	t_room	*front_ptr;
	int		ret;

	front_ptr = frontier;
	while (front_ptr != NULL)
	{
		ret = set_levels(front_ptr, next_f, levels, lem_in);
		if (ret == NEW_PATH)
			return (NEW_PATH);
		front_ptr = front_ptr->id == 0 ? NULL : front_ptr->next_front;
	}
	return (NO_PATH);
}

int		breadth_first_search(t_list *start_ptr, t_lem_in *lem_in)
{
	int		levels;
	int		ret;
	t_room	*frontier;
	t_room	*next_f;

	levels = 1;
	frontier = start_ptr->content;
	while (frontier != NULL)
	{
		next_f = NULL;
		ret = set_frontier(frontier, lem_in, &next_f, levels);
		if (ret == NEW_PATH)
			return (NEW_PATH);
		frontier = next_f;
		levels++;
	}
	return (NO_PATH);
}
