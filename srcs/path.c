/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:14:37 by plagache          #+#    #+#             */
/*   Updated: 2020/03/04 16:26:12 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** input start
** output start or NULL if error
** visit all vertices with positive capacity
*/

int		bfs_neighbours(t_list *front_ptr, t_list **next_l, t_list *frontier)
{
	t_list	*neigh_ptr;

	neigh_ptr = ((t_room*)(front_ptr->content))->neighbours;
	while (neigh_ptr != NULL)
	{
		if (((t_room*)(neigh_ptr->content))->level == 0
			&& ((t_room*)(neigh_ptr->content))->capacity > 0)
		{
			((t_room*)(neigh_ptr->content))->level = levels;
			((t_room*)(neigh_ptr->content))->parent = front_ptr;
			if (new_link(next_l, (t_room*)(neigh_ptr->content)) == FAILURE)
			{
				free(*next_l);
				free(frontier);
				return (FAILURE);
			}
			// make a function to free list properly without freeing content //
		}
		neigh_ptr = neigh_ptr->next;
	}
	return (SUCCESS);
}

int		breadth_first_search(t_list *start_ptr)
{
	int		levels;
	t_list	*frontier;
	t_list	*front_ptr;
	t_list	*next_l;

	levels = 1;
	frontier = start_ptr;
	while (frontier != NULL)
	{
		next_l = NULL;
		front_ptr = frontier;
		while(front_ptr != NULL) 
		{
			if (bfs_frontier(front_ptr, &next_l, frontier) == FAILURE)
				return (FAILURE);
			front_ptr = front_ptr->next;
		}
		free(frontier);
		//free list 
		frontier = next_l;
		levels++;
	}
	return (SUCCESS);
}


t_list	*new_path(t_list *end)
{
	t_list	*ptr;
	t_room	*room;

	ptr = ((t_room*)(end->content))->neighbours; 
	while (ptr != NULL)
	{
		room = (t_room*)ptr->content;
		if (room->capacity == 1 && room->level != 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/*
** get_path
** input end start
** output Path or NULL
** create path and returns it
**   
*/

t_list	*get_path(t_list *end, t_list *neigh)
{
	t_list	*path;
	t_list	*ptr;

	if (new_link(&path, (t_room*)end->content) == FAILURE)
		return (NULL);
	ptr = neigh;
	while (ptr != NULL)
	{
		if (new_link(&path, (t_room*)ptr->content) == FAILURE)
		{
			//free list path
			return (NULL);
		}
		ptr = ((t_room*)(ptr->content))->parent;
	}
	return (path);
}

// input list of path
// failure if malloc of link fail
// malloc ein mayon 
// puting path in mayon content
// then puting mayon at start of path_list
// return SUCCESS if all above goes well

int		add_path(t_list **path_list, t_list *path)
{
	t_list *new_link;

	new_link = (t_list*)ft_memalloc(sizeof(t_list));
	if (new_link == NULL)
		return (FAILURE);
	new_link->content = path;
	ft_lstadd(path_list, new_link);
	return (SUCCESS);
}

int		check_min_path()
{
	//check if start and end has link to any room (non empty neighbours_list for start and end)
}
