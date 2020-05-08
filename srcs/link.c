/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 15:05:21 by plagache          #+#    #+#             */
/*   Updated: 2020/05/07 18:14:15 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*search_room(t_lem_in *info, char *room)
{
	t_list *ptr;

	ptr = info->head;
	while (ptr != NULL
			&& ft_strcmp(((t_room*)ptr->content)->room_name, room) <= 0)
	{
		if (ft_strcmp(((t_room*)ptr->content)->room_name, room) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/*
** comment in function
**	//check if new_link faild and return FAILURE
*/

int		get_link(t_lem_in *info, char *room_name1, char *room_name2)
{
	t_list *ptr1;
	t_list *ptr2;
	t_room *room1;
	t_room *room2;

	ptr1 = search_room(info, room_name1);
	ptr2 = search_room(info, room_name2);
	if (ptr1 == NULL || ptr2 == NULL)
		return (NO_ROOM);
	room1 = (t_room*)(ptr1->content);
	room2 = (t_room*)(ptr2->content);
	if (new_link(&(room2->neighbours), room1) == FAILURE
		|| new_link(&(room1->neighbours), room2) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int		get_links(t_lem_in *info)
{
	char	**arr;
	int		ret;

	while (info->file_split[info->line] != NULL)
	{
		if (is_comment(info->file_split[info->line]) == SUCCESS)
			info->line++;
		else if (is_link(info->file_split[info->line]) == SUCCESS)
		{
			if ((arr = ft_strsplit(info->file_split[info->line], '-')) == NULL)
				return (FAILURE);
			ret = get_link(info, arr[0], arr[1]);
			free_arr((void**)arr);
			if (ret == FAILURE)
				return (FAILURE);
			else if (ret == NO_ROOM)
				return (SUCCESS);
			info->line++;
		}
		else
			return (SUCCESS);
	}
	return (SUCCESS);
}
