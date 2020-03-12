/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:55:54 by plagache          #+#    #+#             */
/*   Updated: 2020/02/27 16:51:01 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		new_link(t_list **head, t_room *room_ptr)
{
	t_room *room;
	t_list *new;

	room = room_ptr;
	if (room == NULL)
		room = (t_room*)ft_memalloc(sizeof(t_room));
	if (room == NULL)
		return (FAILURE);
	new = ft_lstnew(0, 0);
	if (new == NULL)
		return (FAILURE);
	new->content = room;
	new->content_size = sizeof(t_room);
	ft_lstadd(head, new);
	return (SUCCESS);
	/* free room if link fail*/
}
