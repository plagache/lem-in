#include "lem_in.h"

/*
** input start
** output start or NULL if error
** visit all vertices with positive capacity
*/

int		bfs_neighbours(t_list *front_ptr, t_list **next_l, t_list *frontier)
{
	t_list	*neigh_ptr;

	neigh_ptr = ((t_room*)(front_ptr->content))->neighbours;
	while (neigh_ptr != NULL)
	{
		if (((t_room*)(neigh_ptr->content))->level == 0
			&& ((t_room*)(neigh_ptr->content))->capacity > 0)
		{
			((t_room*)(neigh_ptr->content))->level = levels;
			((t_room*)(neigh_ptr->content))->parent = front_ptr;
			if (new_link(next_l, (t_room*)(neigh_ptr->content)) == FAILURE)
			{
				//free list (*next_l);
				//free list (frontier);
				return (FAILURE);
			}
			// make a function to free list properly without freeing content //
		}
		neigh_ptr = neigh_ptr->next;
	}
	return (SUCCESS);
}

int		breadth_first_search(t_list *start_ptr)
{
	int		levels;
	t_list	*frontier;
	t_list	*front_ptr;
	t_list	*next_l;

	levels = 1;
	frontier = start_ptr;
	while (frontier != NULL)
	{
		next_l = NULL;
		front_ptr = frontier;
		while(front_ptr != NULL) 
		{
			if (bfs_neighbours(front_ptr, &next_l, frontier) == FAILURE)
				return (FAILURE);
			front_ptr = front_ptr->next;
		}
		free(frontier);
		//free list 
		frontier = next_l;
		levels++;
	}
	return (SUCCESS);
}

/*
** input (...)
** output(flow) >= 0 SUCCESS || -1 ERROR of malloc anywhere
** call:
** -BFS() to propagate paths
** -create_path() to add path to list
** -raise flow by 1
** -loop STOP WHEN CREATE PATH SAYS NO MORE PATH
** 
*/
int		max_flow(t_list **path_list, t_list *end, t_list *start, t_list *head)
{
	int	flow;
	int	ret;

	flow = 0;
	while (ret != NO_PATH)
	{
		ret = breadth_first_search(t_list *start);
		if (ret == FAILURE)
			return (-1);
		ret = create_path(path_list, end, head);
		if (ret == PATH_FAIL || ret == LIST_FAIL)
			return (-1);
		flow++;
	}
	return (flow);
}
