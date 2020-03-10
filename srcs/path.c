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
#include "ft_printf.h"

t_list	*new_path(t_list *end)
{
	t_list	*ptr;
	t_room	*room;

	room = (t_room*)end->content;
	ptr = room->neighbours; 
	while (ptr != NULL)
	{
		room = (t_room*)(ptr->content);
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
	size_t	lenght;

	path = NULL;
	if (new_link(&path, (t_room*)(end->content)) == FAILURE)
		return (NULL);
	ptr = neigh;
	lenght = 0;
	while (ptr != NULL)
	{
		if (new_link(&path, (t_room*)ptr->content) == FAILURE)
		{
			//free list path
			return (NULL);
		}
		ptr = ((t_room*)(ptr->content))->parent;
		lenght++;
	}
	path->content_size = lenght - 1;
	ft_printf("path size |%u|\n", path->content_size);
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
	{
		//free list path
		return (FAILURE);
	}
	new_link->content = path;
	ft_lstadd(path_list, new_link);
	return (SUCCESS);
}

/*
** input (...)
** set path capacity to 0
** and reset levels in all non paths nodes (capacity == 1)
** output(nothing)
*/

/*
** input (end, path_list)
** will call new_/get_/add_path
** output (SUCCES if all calls returned SUCCESS or not NULL)
** (FAILURE if any of the procedure returned FAILURE or NULL)
*/

int		create_path(t_list **path_list, t_list *start, t_list *end,
					t_list *head)
{
	t_list	*neigh;
	t_list	*path;

	neigh = new_path(end);
	if (neigh == NULL)
		return (NO_PATH);
	path = get_path(end, neigh);
	if (path == NULL)
	{
		//free list (path_list);
		return (PATH_FAIL);
	}
	if (add_path(path_list, path) == FAILURE)
	{
		//free list path_list and path inside
		return (LIST_FAIL);
	}
	clean_path(path, head, start);
	return (SUCCESS);
}
