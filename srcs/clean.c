#include "lem_in.h"
#include "ft_printf.h"

void	free_list(t_list *lst)
{
	if (lst->next != NULL)
		free_list(lst->next);
	lst->content = NULL;
	free(lst);
}

void	free_graph(t_list *head)
{
	t_room	*room;

	if (head->next != NULL)
		free_graph(head->next);
	room = (t_room*)head->content;
	free_list(room->neighbours);
	free(room->room_name);
	free(room);
	free(head);
}

void	free_matrice(char **matrice, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(matrice[i]);
	free(matrice);
}

void	free_paths(t_list **paths, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free_list(paths[i]);
	free(paths);
}
