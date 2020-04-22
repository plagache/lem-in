/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 15:35:56 by alagache          #+#    #+#             */
/*   Updated: 2020/04/22 16:47:18 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

/*
** utils ants_to_move
*/

int8_t	ants_to_move(t_path *paths, int flow)
{
	int	i;

	i = -1;
	while (++i < flow)
	{
		if (paths[i].out != paths[i].ants)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

/*
** core move ant
*/

int8_t	move_ant(t_room *dst, t_room *src, int *space)
{
	dst->ant_id = src->ant_id;
	src->ant_id = 0;
	if (*space == 1 && ft_printf(" L%i-%s", dst->ant_id, dst->room_name) == -1)
		return (FAILURE);
	if (*space == 0 && ft_printf("L%i-%s", dst->ant_id, dst->room_name) == -1)
		return (FAILURE);
	if (*space == 0)
		*space = 1;
	return (SUCCESS);
}

int8_t	move_new_ant(t_path *path, t_room *room, int *next_ant, int *space)
{
	room->ant_id = *next_ant;
	(*next_ant)++;
	path->in++;
	if (*space == 0
		&& ft_printf("L%i-%s", room->ant_id, room->room_name) == -1)
		return (FAILURE);
	if (*space == 1
		&& ft_printf(" L%i-%s", room->ant_id, room->room_name) == -1)
		return (FAILURE);
	if (*space == 0)
		*space = 1;
	return (SUCCESS);
}

/*
** inner move_path
*/

int8_t	move_path(t_path *path, int *next_ant, int move)
{
	t_list	*ptr;

	ptr = path->list;
	while (ptr->next->next != NULL)
	{
		if (((t_room*)(ptr->next)->content)->ant_id != 0)
		{
			if (move_ant(ptr->content,
				(t_room*)(ptr->next)->content, &move) == FAILURE)
				return (FAILURE);
			if (((t_room*)ptr->content)->id == 1)
				path->out++;
		}
		ptr = ptr->next;
	}
	if (path->in != path->ants)
	{
		if (move_new_ant(path, ptr->content, next_ant, &move) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

/*
** outer iterate over paths
*/

int8_t	move_paths(int flow, t_path *paths)
{
	int	next_ant;
	int	i;
	int	move;

	next_ant = 1;
	while (ants_to_move(paths, flow) == TRUE)
	{
		i = -1;
		move = 0;
		while (++i < flow)
		{
			if (paths[i].out != paths[i].ants)
			{
				if (move_path(paths + i, &next_ant, move) == FAILURE)
					return (FAILURE);
				move = 1;
			}
		}
		if (ft_printf("\n") == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}
