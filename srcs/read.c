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

/*
void	print_roomnames(t_room *room)
{
	t_room *R_ptr;
	t_list *lst;
	int	nbr;

	nbr = 1;
//	ROOM || neighbours (list) ||
//	neighbours || content is t_room  || content->room_name
	//printf("LINK NAME = |%s|\n", ((t_room*)ptr->content)->room_name);
	if (room == NULL)
	{
		printf (" ROOM IS NULL\n");
		exit (0);
	}
	lst = room->neighbours;
	if (lst == NULL)
	{
		printf ("neighbours is NULL in room %s \n", room->room_name);
		exit (0);
	}
	printf ("neighbours of room %s \n", room->room_name);
	while (lst != NULL)
	{
		R_ptr = (t_room*)lst->content;
		printf("||Neighbour No =%i\n|Name = %s\n| address = %p\n", nbr, R_ptr->room_name, R_ptr);
		lst = lst->next;
		nbr++;
	}
}

*/
int	display_list(t_lem_in *info)
{
	int c;
	t_list *ptr;
	t_room *rptr;

	c = 1;
	ptr = info->head;
	while (ptr != NULL)
	{
		rptr = (t_room*)(ptr->content);
		printf("ROOM NBR IS|%i|\n", c);
		printf("ROOM NAME IS|%s|\n", rptr->room_name);
		printf("ROOM ADDRESS IS|%p| in link|%p|\n\n", rptr, ptr);
		ptr = ptr->next;
	}
	return (0);
}

int		print_neighbours(t_list *neighbours)
{
	t_room	*room_ptr;
	t_list	*ptr;
	int		nbr;

	
	if (neighbours == NULL)
		return (FAILURE);
	nbr = 1;
	ptr = neighbours;
	while (ptr != NULL)
	{
		room_ptr = (t_room*)ptr->content;
		if (room_ptr != NULL)
			printf("Neighbour No |%i|\nis |%s|\n", nbr, room_ptr->room_name);
		else
			printf("NO ROOM PTR\n");
		nbr++;
		ptr = ptr->next;
	}
	return (0);
}

int		display_data(t_lem_in *info)
{
	t_list	*head_ptr;
	t_room	*room_ptr;

	head_ptr = info->head;
	while (head_ptr != NULL)
	{
		if ((t_room*)head_ptr->content != NULL)
		{
			room_ptr = (t_room*)head_ptr->content;
			printf("|%s| NEIGHBOURS ARE\n", room_ptr->room_name);
			if (print_neighbours((t_list*)room_ptr->neighbours) == FAILURE)
				return (FAILURE);
		}
		head_ptr = head_ptr->next;
	}
	return (0);
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
