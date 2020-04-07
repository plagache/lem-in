
#include "lem_in.h"
#include "ft_printf.h"

void	update_flow(t_list *end, t_list *start, char **m_flow, int *len)
{
	t_room	*ptr;
	t_room	*parent;

	ptr = end->content;
	//(void)start;
	while (ptr != start->content/* && ((t_room*)(ptr->content))->parent != NULL*/)
	{
		parent = ptr->parent;
//		ft_printf("addr parent = ||%p||\n", parent);
//		ft_printf("add parent content %p\n", ((t_room*)(parent->content)));
//		ft_printf("parent name ||%s|| id parent = ||%i||\n", parent->room_name, parent->id);
//		ft_printf("ptr name ||%s|| id ptr = ||%i||\n", ptr->room_name, ptr->id);
		if (ptr->flow == 0 && ptr != end->content)
			ptr->flow++;
		m_flow[parent->id][ptr->id]++;
		m_flow[ptr->id][parent->id]--;
		ptr = parent;
		*len = *len + 1;
	}
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
		((t_room*)ptr->content)->next_front = NULL;
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
//		ft_printf("before BFS\n");
		ret = breadth_first_search(lem_in->start_ptr, lem_in);
//		ft_printf("flow = ||%i|| ret = ||%i||\n after BFS\n", flow, ret);
		if (ret == NO_PATH)
			return (flow);
		else
		{
			ret = 0;
			update_flow(lem_in->end_ptr, lem_in->start_ptr, lem_in->m_flow, &ret);
			clean_graph(lem_in);
			flow++;
			if (lem_in->nbr_ants * 16 < ret * flow * 8)
				return (flow);
		}
	}
	return (DEBUG);
}
