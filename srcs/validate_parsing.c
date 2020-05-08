/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 15:01:40 by plagache          #+#    #+#             */
/*   Updated: 2020/04/14 15:01:42 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		fail_links(t_list *head)
{
	t_list	*ptr;
	t_room	*room;

	ptr = head;
	while (ptr != NULL)
	{
		room = ptr->content;
		if ((room->command == END_COMMAND || room->command == START_COMMAND)
			&& room->neighbours == NULL)
			return (FAILURE);
		ptr = ptr->next;
	}
	return (SUCCESS);
}

/*
** duplicate link / room
** parse the list of room next have same name
** if ptr->content == ptr->next->content
** this is an error
*/

int	duplicate_room(t_list *head)
{
	t_list	*ptr;
	char	*str1;
	char	*str2;

	ptr = head;
	while (ptr->next != NULL)
	{
		str1 = ((t_room*)ptr->content)->room_name;
		str2 = ((t_room*)(ptr->next)->content)->room_name;
		if (ft_strcmp(str1, str2) == 0)
			return (SUCCESS);
		ptr = ptr->next;
	}
	return (FAILURE);
}

/*
** if char command has more than 1 bit set == ERROR
** //start and end on a different room
*/

int	command(t_list *start, t_list *end)
{
	if (start == end)
		return (FAILURE);
	return (SUCCESS);
}

/*
** if Start has End as neighbour == ERROR
*/

int	ultimate_path(t_list *start, t_list *end)
{
	t_list	*ptr;

	ptr = ((t_room*)start->content)->neighbours;
	while (ptr != NULL)
	{
		if (ptr->content == end->content)
			return (FAILURE);
		ptr = ptr->next;
	}
	return (SUCCESS);
}

int	validate_data(t_lem_in *info)
{
	if (command(info->start_ptr, info->end_ptr) == FAILURE
		|| ultimate_path(info->start_ptr, info->end_ptr) == FAILURE
		|| duplicate_room(info->head) == SUCCESS
		|| fail_links(info->head) == FAILURE)
	{
		ft_printf("ERROR\n");
		free_graph(info->head, 3);
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	return (SUCCESS);
}
