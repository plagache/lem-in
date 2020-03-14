#include "lem_in.h"
#include "ft_printf.h"

t_list	**create_path_array(int flow)
{
	t_list	**arr;

	arr = (t_list**)ft_memalloc(sizeof(t_list*) * flow);
	if (arr == NULL)
		return (NULL);
	return (arr);
}

/*
input
get_path(matrice, start, neigh, t_list *path)
	procedure
	- add start to path
	- find next neigh with positive flow
	- call again (neigh , neigh-neigh) 

output t_list*
*/

int		get_path(char **matrice, t_list *start, t_list *neigh, t_list **path)
{
	t_list *ptr;

	if (new_link(path, (t_room*)start->content) == FAILURE)
	{
		//free_list(*path);
		return (FAILURE);
	}
	ptr = neigh;
	while (ptr != NULL)
	{
		if (matrice[((t_room*)start->content)->id][((t_room*)ptr->content)->id] == 1)
		{
			if (get_path(matrice, ptr, ((t_room*)ptr->content)->neighbours, path) == FAILURE)
			{
				//free_list(*path);
				return (FAILURE);
			}
			return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (SUCCESS);
}

/*
** take out the path of the graph
** remove flow from end and next && next and start
** remove flow for every edges that exist with Vertices of the path;
** input matrice path;
** output nothing

//need to change input to take only lem_in and init room_nbr to be used

void	remove_flow(char **matrice, int size, t_list *path)
{
	t_list	*ptr;
	int		i;

	ptr = path;
	//remove flow with end;
	while (((t_room*)ptr->content)->id != 0)
	{
		//remove flow with id of Vertice;
		i = -1;
		while (++i < size)
		{
			matrice[i][id] = 0;
			matrice[id][i] = 0;
		}
		//flow remove
		ptr = ptr->next;
	}
	//remove flow with start;
}

*/
/*
input matrice, arr of t_list *, start_ptr
t_list neigh
while i < flow
 call get_path(matrice, start, neigh)
i++
output fail or success
*/

int		add_paths(char **matrice, t_list **paths, t_list *start, int flow)
{
	t_list	*neigh;
	int		i;

	i = 0;
	neigh = ((t_room*)start->content)->neighbours;
	while (i < flow)
	{
		ft_printf("ieme before get_path||%i||\n", i);
		if (get_path(matrice, start, neigh, paths + i) == FAILURE)
		{
			//clean(paths);
			return (FAILURE);
		}
		//remove flow;
		matrice[((t_room*)start->content)->id][((t_room*)neigh->content)->id] = 0;
		neigh = neigh->next;
		i++;
	}
	return (SUCCESS);
}

int		path(t_lem_in *lem_in, int flow)
{
	lem_in->paths = create_path_array(flow);
	if (add_paths(lem_in->m_flow, lem_in->paths, lem_in->start_ptr, flow) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
