/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 14:28:31 by plagache          #+#    #+#             */
/*   Updated: 2020/04/14 14:28:34 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		path_len(t_list *path)
{
	t_list	*ptr;
	int		len;

	len = 0;
	ptr = path;
	while (ptr != NULL)
	{
		len++;
		ptr = ptr->next;
	}
	return (len - 2);
}

/*
** free room if link fail
*/

int		new_link(t_list **head, t_room *room_ptr)
{
	t_room *room;
	t_list *new;

	new = ft_lstnew(0, 0);
	if (new == NULL)
		return (FAILURE);
	room = room_ptr;
	if (room == NULL)
		room = (t_room*)ft_memalloc(sizeof(t_room));
	if (room == NULL)
	{
		free(new);
		return (FAILURE);
	}
	new->content = room;
	new->content_size = sizeof(t_room);
	ft_lstadd(head, new);
	return (SUCCESS);
}
