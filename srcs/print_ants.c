#include "lem_in.h"
#include "ft_printf.h"

//utils ants_to_move

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

//core move ant

int8_t	move_ant(t_room *dst, t_room *src)
{
	dst->ant_id = src->ant_id;
	src->ant_id = 0;
	if (ft_printf("L%i-%s ", dst->ant_id, dst->room_name) == -1)
		return (FAILURE);
	return (SUCCESS);
}
//inner move_path

int8_t	move_path(t_path *path, int *next_ant)
{
	t_list	*ptr;

	ptr = path->list;
	while (ptr->next->next != NULL)
	{
		if (((t_room*)(ptr->next)->content)->ant_id != 0)
		{
			if (move_ant(ptr->content, (t_room*)(ptr->next)->content) == FAILURE)
				return (FAILURE);
			if (((t_room*)ptr->content)->id == 1)
				path->out++;
		}
		ptr = ptr->next;
	}
	if (path->in != path->ants)
	{
		((t_room*)ptr->content)->ant_id = *next_ant;
		(*next_ant)++;
		path->in++;
		if (ft_printf("L%i-%s ", ((t_room*)ptr->content)->ant_id,
			((t_room*)ptr->content)->room_name) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}

//outer iterate over paths
int8_t	move_paths(int flow, t_path *paths)
{
	int	next_ant;
	int	i;

	next_ant = 1;
	while (ants_to_move(paths, flow) == TRUE)
	{
		i = -1;
		while (++i < flow)
		{
			if (paths[i].out != paths[i].ants)
			{
				if (move_path(paths + i, &next_ant) == FAILURE)
					return (FAILURE);
			}
		}
		if (ft_printf("\n") == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}
