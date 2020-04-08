/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:00:38 by alagache          #+#    #+#             */
/*   Updated: 2020/03/18 08:25:17 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int	display_list(t_list *list)
{
	t_list	*ptr;
	t_room	*rptr;
	int		c;

	c = 1;
	ptr = list;
	while (ptr != NULL)
	{
		rptr = (t_room*)(ptr->content);
//		ft_printf("ROOM NBR IS|%i|", c);
		ft_printf("ROOM NAME IS|%6s| ID = |%6i|\n", rptr->room_name, rptr->id);
//		ft_printf("ROOM ADDRESS IS|%p| in link|%p|\n\n", rptr, ptr);
//		ft_printf("ROOM|%s|ID |%i|>>", rptr->room_name, rptr->id);
		c++;
		ptr = ptr->next;
	}
	return (0);
}

int		print_neighbours(t_room *room)
{
	t_room	*room_ptr;
	t_list	*ptr;
	int		nbr;

	ft_printf("addrr |%p|\n", room->neighbours);
	if (room->neighbours == NULL)
		return (FAILURE);
	nbr = 1;
	ptr = room->neighbours;
	while (ptr != NULL)
	{
		room_ptr = (t_room*)(ptr->content);
		if (room_ptr != NULL)
			ft_printf("Neighbour No |%i|is |%s|\n", nbr, room_ptr->room_name);
		else
			ft_printf("NO ROOM PTR\n");
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
			room_ptr = (t_room*)(head_ptr->content);
			ft_printf("|%s| NEIGHBOURS ARE\n", room_ptr->room_name);
			if (print_neighbours(room_ptr) == FAILURE)
				ft_printf("fail to print neighbours\n");
		}
		head_ptr = head_ptr->next;
	}
	return (0);
}

int		display_paths(t_path *paths, int flow)
{
	int i;

	i = 0;
	while (i < flow)
	{
		ft_printf("Path n |%i|len n |%i|\n", i + 1, paths[i].len);
		display_list(paths[i].list);
		i++;
	}
	return (SUCCESS);
}

void	print_farm(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
	ft_printf("\n");
}
