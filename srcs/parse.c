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

int		get_ants(t_lem_in *info)
{
	int		line;
	int 	c;

	c = 0;
	line = 0;
	while (is_command(info->file_split[line]) == FAILURE
			&& is_comment(info->file_split[line]) == SUCCESS)
	line++;
	while (ft_isdigit(info->file_split[line][c]) == TRUE)
		c++;
	if (info->file_split[line][c] != '\0')
		return (FAILURE);
	info->line_ants = line;
	info->nbr_ants = ft_atol(info->file_split[line]);
	info->line = line + 1;
	return (SUCCESS);
}

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
		return (FAILURE);
	/* free room then link*/
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

int		get_start(char **file, int line, t_lem_in *info)
{
	int		len;
	t_list	*ptr;

	while (ft_strcmp("##start", file[line]) != 0 && line < info->line)
		line++;
	if (line == info->line)
		return (FAILURE);
	while (is_room(file[line]) == FAILURE && line < info->line)
		line++;
	if (line == info->line)
		return (FAILURE);
	len = ft_strchr(file[line], ' ') - file[line];
	ptr = info->head;
	while (ptr != NULL && ft_strncmp(file[line], ((t_room*)(ptr->content))->room_name, len) != 0)
		ptr = ptr->next;
	if (ptr == NULL)
		return (FAILURE);
	((t_room*)(ptr->content))->command ^= START_COMMAND;
	((t_room*)(ptr->content))->level = -1;
	info->start_ptr = ptr;
	return (SUCCESS);
}

int		get_end(char **file, int line, t_lem_in *info)
{
	int		len;
	t_list	*ptr;

	while (ft_strcmp("##end", file[line]) != 0 && line < info->line)
		line++;
	if (line == info->line)
		return (FAILURE);
	while (is_room(file[line]) == FAILURE && line < info->line)
		line++;
	if (line == info->line)
		return (FAILURE);
	len = ft_strchr(file[line], ' ') - file[line];
	ptr = info->head;
	while (ptr != NULL && ft_strncmp(file[line], ((t_room*)(ptr->content))->room_name, len) != 0)
		ptr = ptr->next;
	if (ptr == NULL)
		return (FAILURE);
	((t_room*)(ptr->content))->command ^= END_COMMAND;
	info->end_ptr = ptr;
	return (SUCCESS);
}

int		get_commands(t_lem_in *info)
{
	sort_function(info->head);
	if (get_start(info->file_split, info->line_ants, info) == FAILURE)
		return (FAILURE);
	if (get_end(info->file_split, info->line_ants, info) == FAILURE)
		return (FAILURE);
	//display_list(info);
	return (SUCCESS);
	//free list and file
}

t_list	*search_room(t_lem_in *info, char *room)
{
	t_list *ptr;
	
	ptr = info->head;
	while (ptr != NULL && ft_strcmp(((t_room*)ptr->content)->room_name, room) <= 0)
	{
		if (ft_strcmp(((t_room*)ptr->content)->room_name, room) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int		get_link(t_lem_in *info, char *room_name1, char *room_name2)
{
	t_list *ptr1;
	t_list *ptr2;
	t_room *room1;
	t_room *room2;

	ptr1 = search_room(info, room_name1);
	ptr2 = search_room(info, room_name2);
	if (ptr1 == NULL || ptr2 == NULL)
		return (FAILURE);
	room1 = (t_room*)(ptr1->content);
	room2 = (t_room*)(ptr2->content);
	new_link(&(room2->neighbours), room1);
	new_link(&(room1->neighbours), room2);
	//check if new_link faild and return FAILURE
	return (SUCCESS);
}

int		get_links(t_lem_in *info)
{
	char **arr;

	while (info->file_split[info->line] != NULL)
	{
		if (is_comment(info->file_split[info->line]) == SUCCESS)
			info->line++;
		else if (is_link(info->file_split[info->line]) == SUCCESS) 
		{
			arr = ft_strsplit(info->file_split[info->line], '-');
			get_link(info, arr[0], arr[1]);
			free_arr((void**)arr);
			info->line++;
		}
		else
			return (FAILURE);
	}
	//display_data(info);
	return (SUCCESS);
}
