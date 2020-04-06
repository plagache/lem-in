#include "lem_in.h"
#include "ft_printf.h"

t_path	*create_path_array(int flow)
{
	t_path	*arr;

	arr = (t_path*)ft_memalloc(sizeof(t_path) * flow);
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
		free_list(*path);
		return (FAILURE);
	}
	ptr = neigh;
	while (ptr != NULL)
	{
		if (matrice[((t_room*)start->content)->id][((t_room*)ptr->content)->id]
			== 1)
		{
			if (get_path(matrice, ptr, ((t_room*)ptr->content)->neighbours,
				path) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (SUCCESS);
}

/*
** takes a t_list ** and a flow matrice
** find the link between start and it s neighbours and remove flow between them
*/

void	remove_flow(t_list **path, char **matrice)
{
	t_list *ptr;

	ptr = *path;
	while (ptr->next != NULL && ((t_room*)(ptr->next)->content)->id != 0)
		ptr = ptr->next;
	matrice[((t_room*)ptr->content)->id][0] = 0;
	matrice[0][((t_room*)ptr->content)->id] = 0;
}

/*
input matrice, arr of t_list *, start_ptr
t_list neigh
while i < flow
 call get_path(matrice, start, neigh)
i++
output fail or success
*/

int		add_paths(char **matrice, t_path *paths, t_list *start, int flow)
{
	t_list	*neigh;
	int		i;

	i = 0;
	neigh = ((t_room*)start->content)->neighbours;
	while (i < flow)
	{
		if (get_path(matrice, start, neigh, &((paths + i)->list)) == FAILURE)
		{
			//clean(paths);
			return (FAILURE);
		}
		remove_flow(&((paths + i)->list), matrice);
		(paths + i)->len = path_len((paths + i)->list);
		i++;
	}
	return (SUCCESS);
}

int		path(t_lem_in *lem_in, int *flow)
{
	lem_in->paths = create_path_array(*flow);
	if (lem_in->paths == NULL)
		return (FAILURE);
	if (add_paths(lem_in->m_flow, lem_in->paths, lem_in->start_ptr, *flow) == FAILURE)
		return (FAILURE);
	sort_paths(lem_in->paths, *flow);
	if (check_collision(&lem_in->paths, flow) == FAILURE)
	{
		free_paths(lem_in->paths, *flow);
		return (FAILURE);
	}
	split_ants(lem_in->nbr_ants, *flow, lem_in->paths);
	//display_paths(lem_in, *flow);
	//ft_printf("no collisiob flow is %i", *flow);
	if (move_paths(*flow, lem_in->paths) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
