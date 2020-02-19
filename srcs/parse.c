/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:55:54 by plagache          #+#    #+#             */
/*   Updated: 2020/02/19 17:06:12 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		new_link(t_list *head)
{
	t_room *room;
	t_list *new;

	room = (t_room *)malloc(sizeof(t_room));
	if (room == NULL);
		return (FAILURE);
	new = ft_lstnew(room, sizeof(t_room));
	if (new == NULL);
		return (FAILURE);
	ft_lstadd(&head, new);
	return (SUCCESS);
	/* free room if link fail*/
}

int		fill_room_name(t_list *new, char *line)
{
	char	*ptr;
	size_t	len;

	ptr = ft_strchr(line, ' ');
	len = ptr - line;
	new->content->room_name = (char *)malloc(sizeof(char) * (len + 1));
	if (new->content->room_name == NULL)
		return (FAILURE);
	new->content->room_name[len] = '\0';
	ft_strncpy(new->content->room_name, line, len);
	return (SUCCESS);
}

int		get_room_info(t_lem_in *info)
{
	if (is_room(info->file_split[info->line]) == FAILURE)
		return (FAILURE);
	new_link(info->head);
	if (info->head == NULL)
		return (FAILURE);
	if (fill_room_name(info->head, info->file_split[info->line]) == FAILURE)
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
		if (get_room_info(info) == FAILURE);
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
	while (ptr != NULL && ft_strncmp(file[line], ptr->content->room_name, len) != 0)
		ptr = ptr->next;
	if (ptr == NULL)
		return (FAILURE);
	ptr->content->command ^= 1;
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
	while (ptr != NULL && ft_strncmp(file[line], ptr->content->room_name, len) != 0)
		ptr = ptr->next;
	if (ptr == NULL)
		return (FAILURE);
	ptr->content->command ^= 128;
	info->end_ptr = ptr;
	return (SUCCESS);
}

int		get_commands(t_lem_in * info)
{
	if (get_start(info->file_split, info->line_ants, info) == FAILURE)
		return (FAILURE);
	if (get_end(info->file_split, info->line_ants, info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
	//free list and file
}

// sort room list by rooms names let us:
	//search for a roomname:to_find 
	//until to_find is before roomname in lexicographical order (means ft_strcmp(to_compare, to_find) is negative) in that order
	//or no more nodes in list to check
	//if ERROR as said above
	//return ERROR
	//return room_ptr;

	//add_to_neighbours(t_list *to_add, t_list *neighbours)
	// ROOM1, ROOM2->neighbours

int			get_link(t_lem_in *info, char *room_name1, char *room_name2)
{
	t_list *ptr1;
	t_list *ptr2;

	ptr1 = is_room(info, room_name1);
	ptr2 = is_room(info, room_name2);
	if (ptr1 == NULL || ptr2 == NULL)
		return (FAILURE);
	ft_lstadd(&(ptr1->neighbours), ptr2);
	ft_lstadd(&(ptr2->neighbours), ptr1);
	return (SUCCESS)
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
	return (SUCCESS);
	//iterate over lines
	// call get_link if he is on a link line
}

int		is_room(t_lem_in *info, char *room)
{
	t_list *ptr;
	
	ptr = info->head;
	while (ptr != NULL && ft_strcmp(ptr->content->room_name, room) <= 0)
	{
		if (ft_strcmp(ptr->content->room_name, room) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/*
** VALIDATE DATA BEFORE SEARCHING FOR SOLUTION IN IT
** means check all assupmtions made before 
** if char command has more than 1 bit set == ERROR
** if Start has End as neighbour == ERROR
*/
/* sorted room */
/* find room pointer function*/

/*
** MAKEFILE compile 
** print lem-in 
** check parsing
*/
