/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:03:56 by plagache          #+#    #+#             */
/*   Updated: 2020/05/07 18:36:48 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		mv_to_next_room(t_lem_in *info)
{
	while (info->file_split[info->line] != NULL &&
		(is_command(info->file_split[info->line]) == SUCCESS
		|| is_comment(info->file_split[info->line]) == SUCCESS))
		info->line++;
	if (info->file_split[info->line] == NULL
		|| is_link(info->file_split[info->line]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int		fill_room(t_list *new, char *line)
{
	char	*ptr;
	size_t	len;

	ptr = ft_strchr(line, ' ');
	len = ptr - line;
	ptr = (char*)ft_memalloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (FAILURE);
	ft_strncpy(ptr, line, len);
	((t_room*)(new->content))->room_name = ptr;
	((t_room*)(new->content))->level = 0;
	return (SUCCESS);
}

int		get_room_info(t_lem_in *info)
{
	if (is_room(info->file_split[info->line]) == FAILURE)
		return (FAILURE);
	new_link(&(info->head), NULL);
	if (info->head == NULL)
		return (FAILURE);
	if (fill_room(info->head, info->file_split[info->line]) == FAILURE)
	{
		free(info->head->content);
		free_graph(info->head->next, 2);
		free(info->head);
		return (FAILURE);
	}
	return (SUCCESS);
}

int		get_rooms(t_lem_in *info)
{
	while (info->file_split[info->line] != NULL
			&& is_link(info->file_split[info->line]) == FAILURE)
	{
		if (mv_to_next_room(info) == FAILURE)
			return (SUCCESS);
		if (get_room_info(info) == FAILURE)
			return (FAILURE);
		info->line++;
	}
	return (SUCCESS);
}

/*
** not sure
** if (is_link(info->file_split[info->line]) == SUCCESS)
** return (FAILURE);
*/
