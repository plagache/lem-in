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
	info->nbr_ants = ft_atol(info->file_split[line]);
	info->line = line + 1;
	return (SUCCESS);
}
/* add #AntsLine */

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

int		get_commands(t_lem_in * info)
{
	//get start/get end (info->file_split, line) AntsLine-line
	//find next room & activate bit command in char
}

/*
** if char command has more than 1 bit set == ERROR
** if Start has End as neighbour == ERROR
*/

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

int		get_link(t_lem_in *info)
{
	//check rooms names exist
	//add Room1 pointer to room2 list
	//add Room2 pointer to room1 list
}

/* sorted room */
/* find room pointer function*/


int		check_min_path()
{
	//check if start and end has link to any room (non empty neighbours_list for start and end)
}
