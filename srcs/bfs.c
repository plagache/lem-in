#include "lem_in.h"
#include "ft_printf.h"

/*
 ** input start
 ** output start or NULL if error
 ** visit all vertices with positive capacity
 */

int		set_levels(t_list *front_ptr, t_list **next_f, int levels,
					t_lem_in *lem_in)
{
	t_list	*neigh_ptr;

	neigh_ptr = ((t_room*)(front_ptr->content))->neighbours;
	while (neigh_ptr != NULL)
	{

		if (((t_room*)(neigh_ptr->content))->level == 0
				&& 1 - lem_in->m_flow[((t_room*)(front_ptr->content))->id]
				[((t_room*)(neigh_ptr->content))->id] > 0)
		{
			((t_room*)(neigh_ptr->content))->level = levels;
			((t_room*)(neigh_ptr->content))->parent = front_ptr;
			if (new_link(next_f, (t_room*)(neigh_ptr->content)) == FAILURE)
				return (FAILURE);
			if (lem_in->end_ptr->content == neigh_ptr->content)
				return (NEW_PATH);
		}
		neigh_ptr = neigh_ptr->next;
	}
	return (NO_PATH);
}

int		set_frontier(t_list *frontier, t_lem_in *lem_in, t_list **next_f,
					int levels)
{
	t_list	*front_ptr;
	int		ret;

	front_ptr = frontier;
	while(front_ptr != NULL) 
	{
		ret = set_levels(front_ptr, next_f, levels, lem_in);
		if (ret != NO_PATH)
		{
			if (frontier->content != lem_in->start_ptr->content)
				//free_list(frontier);
			//free_list(*next_f);
			if (ret == FAILURE)
				return (FAILURE);
			return (NEW_PATH);
		}
		front_ptr = (((t_room*)front_ptr->content)->id == 0 ? NULL
						: front_ptr->next);
	}
	return (NO_PATH);
}

int		breadth_first_search(t_list *start_ptr, t_lem_in *lem_in)
{
	int		levels;
	int		ret;
	t_list	*frontier;
	t_list	*next_f;

	levels = 1;
	frontier = start_ptr;
	while (frontier != NULL)
	{
		next_f = NULL;
		ret = set_frontier(frontier, lem_in, &next_f, levels);
		if (ret == FAILURE)
			return (FAILURE);
		if (ret == NEW_PATH)
			return (NEW_PATH);
		if (frontier->content != start_ptr->content)
		{
			//free_list(frontier);
			//free(frontier);
		}
		frontier = next_f;
		levels++;
	}
	return (NO_PATH);
}
