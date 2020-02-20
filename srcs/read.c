#include "lem_in.h"

int	split_file(t_lem_in *info)
{
	info->file_split = ft_strsplit(info->file, '\n');
	if (info->file_split != NULL)
		return (SUCCESS);
	return (FAILURE);
}

int	read_file(t_lem_in *info)
{
	int		ret;
	char	tab[BUFF_SIZE + 1];

	ft_memset(info, 0, sizeof(t_lem_in));
	info->file = ft_strnew(0);
	if (info->file == NULL)
		return (STRNEW_FAILURE);
	while ((ret = read(0, tab, BUFF_SIZE)) > 0)
	{
		tab[ret] = '\0';
		info->file = ft_strjoinfree(1, info->file, tab);
		if (info->file == NULL)
			return (STRJOIN_FAILURE);
	}
	if (ret == 0)
		return (SUCCESS);
	return (FAILURE);
}

void	print_roomnames(t_room *room)
{
	t_room *R_ptr;
	t_list *lst;
	int	nbr;

	nbr = 1;
//	ROOM || neighbours (list) ||
//	neighbours || content is t_room  || content->room_name
	//printf("LINK NAME = |%s|\n", ((t_room*)ptr->content)->room_name);
	lst = room->neighbours;
	printf("in ROOM |%s| there is\n", room->room_name);
	while (lst != NULL)
	{
		R_ptr = (t_room*)lst->content;
		printf("||Neighbour No =%i\n|Name = %s| address = %p\n\n", nbr, R_ptr->room_name, R_ptr);
		lst = lst->next;
		nbr++;
	}
}

int	display_data(t_lem_in *info)
{
	int c;
	t_room *room_ptr;
	t_list *ptr;

	c = 0;
	//print rooms
	ptr = info->head;
	while (ptr != NULL)
	{
		//printf("ROOM PTR  = %p\n", ptr);
		room_ptr = (t_room*)ptr->content;
		//printf("ROOM NAME = |%s|\n", room_ptr->room_name);

		//given a t_room *room list every nieghbours
		print_roomnames(room_ptr);
		//printf("ROOM COMMAND = |%i|\n", (int)room_ptr->command);
		//printf("ROOM NEXT = %p\n", ptr->next);
		//printf("\n");
		ptr = ptr->next;
	}
	return (c);
}

int	master(t_lem_in *info)
{
	read_file(info);
	split_file(info);
	free(info->file);
	if (get_ants(info) == FAILURE
		|| get_rooms(info) == FAILURE
		|| get_commands(info) == FAILURE
		|| get_links(info) == FAILURE)
		return (FAILURE);
	free(info->file_split);
	if (info->file == NULL)
		return (SUCCESS);
	return (FAILURE);
}
