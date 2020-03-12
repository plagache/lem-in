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

		//ft_printf("id neigh = ||%6i|| room neigh = ||%6s|| room front = ||%6s|| id front = ||%6i||\n"\
		//		, ((t_room*)(neigh_ptr->content))->id, ((t_room*)(neigh_ptr->content))->room_name,\
		//		((t_room*)(front_ptr->content))->room_name, ((t_room*)(front_ptr->content))->id);


		if (((t_room*)(neigh_ptr->content))->level == 0
				&& 1 - lem_in->m_flow[((t_room*)(front_ptr->content))->id]
				[((t_room*)(neigh_ptr->content))->id] > 0)
		{
			((t_room*)(neigh_ptr->content))->level = levels;
			((t_room*)(neigh_ptr->content))->parent = front_ptr;
			if (new_link(next_f, (t_room*)(neigh_ptr->content)) == FAILURE)
			{
				//free list (*next_l);
				return (FAILURE);
			}
//			ft_printf("end :||%p|| neigh :||%p||\n", lem_in->end_ptr, neigh_ptr);
			//ft_printf("id front = ||%i|| id neigh = ||%i|| room neigh = ||%s|| room front = ||%s||\n", ((t_room*)(front_ptr->content))->id, ((t_room*)(neigh_ptr->content))->id, ((t_room*)(neigh_ptr->content))->room_name, ((t_room*)(front_ptr->content))->room_name);
			if (lem_in->end_ptr->content == neigh_ptr->content)
				return (NEW_PATH);
			// make a function to free list properly without freeing content //
		}
//			ft_printf("levels = ||%i||\n", ((t_room*)(neigh_ptr->content))->level);
//			ft_printf("residual = ||%i||\n", 1 - lem_in->m_flow[((t_room*)(front_ptr->content))->id]
//			[((t_room*)(neigh_ptr->content))->id]);
		neigh_ptr = neigh_ptr->next;
	}
	//ft_printf("levels = |%i|\n", levels);
	//display_list(*next_f);
	return (NO_PATH);
}

int		set_frontier(t_list *frontier, t_lem_in *lem_in, t_list **next_f, int levels)
{
	t_list	*front_ptr;
	int		ret;

	front_ptr = frontier;
	while(front_ptr != NULL) 
	{
		ret = set_levels(front_ptr, next_f, levels, lem_in);
		if (ret == FAILURE)
		{
			//if (frontier != lem_in->start_ptr)
			//	free frontier;
			return (FAILURE);
		}
		if (ret == NEW_PATH)
			return (NEW_PATH);
		front_ptr = (((t_room*)front_ptr->content)->id == 0 ? NULL : front_ptr->next);
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
		//if (frontier != start_ptr)
			//free(frontier);
		frontier = next_f;
		levels++;
	}
	return (NO_PATH);
}

/*
 **REWORK THIS TO USE M_FLOW
 **1_ try to find an augmentng path with BFS
 **if no more aug path FLOW is max return flow
 **2_ if has augmenting path update flows rewinding the aug path
 **3_ If flow is enough for ant number return flow
 **else loop the EK
 **
 **1_ use residual capacity to propagate BFS an stop when End has a parent;
 **	//residual capacity is 1 - m_flow[frontier][neighbour] > 0 can be visited
 **2_ update_flows(from end along aug_path)
 **	//reset visited state
 **3_ ^_^
 */
/*
** update_flow
** update flow between parent and ptr along the new augmentng path
** set flow 1 between [parent][ptr]
** set flow -1 between [ptr][parent]
*/

void	update_flow(t_list *end, t_list *start, char **m_flow)
{
	t_list	*ptr;
	t_list	*parent;

	ptr = end;
	//(void)start;
	while (ptr != start /*&& ((t_room*)(ptr->content))->parent != NULL*/)
	{
		parent = ((t_room*)(ptr->content))->parent;
//		ft_printf("addr parent = ||%p||\n", parent);
//		ft_printf("add parent content %p\n", ((t_room*)(parent->content)));
//		ft_printf("id parent = ||%i||\n", ((t_room*)(parent->content))->id);
//		ft_printf("id ptr = ||%i||\n", ((t_room*)(ptr->content))->id);
		m_flow[((t_room*)(parent->content))->id][((t_room*)(ptr->content))->id] = 1;
		m_flow[((t_room*)(ptr->content))->id][((t_room*)(parent->content))->id] = -1;
		ft_printf("flow|\n");
		ptr = parent;
	}
		ft_printf("end flow update|\n");
}

/*
 ** input Start, end, matrice_flow,
 ** Processe
 ** BFS
 ** 		1 NEW PATH
 **			return NOT MAX
 ** 		2 NO PATH
 **			return MAX
 */

/*
 * reset all nodes lvl 
 * reset all nodes parent
 * set start lvl at -1;
*/
void	clean_graph(t_lem_in *lem_in)
{
	t_list	*ptr;

	ptr = lem_in->head;
	while (ptr != NULL)
	{
		((t_room*)ptr->content)->level = 0;
		((t_room*)ptr->content)->parent = NULL;
		ptr = ptr->next;
	}
	((t_room*)lem_in->start_ptr->content)->level = -1;
}

int		edmond_karp(t_lem_in *lem_in)
{
	int	flow;
	int	ret;

	flow = 0;
	while (1)
	{
		ft_printf("before BFS\n");
		ret = breadth_first_search(lem_in->start_ptr, lem_in);
		ft_printf("flow = ||%i|| ret = ||%i||\n after BFS\n", flow, ret);
		if (ret == FAILURE)
			return (-1);
		else if (ret == NO_PATH)
			return (flow);
		else
		{
			update_flow(lem_in->end_ptr, lem_in->start_ptr, lem_in->m_flow);
			clean_graph(lem_in);
			flow++;
		}
		//is flow_enough for ants to optimize search
	}
	return (DEBUG);
}
