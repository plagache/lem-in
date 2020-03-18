#include "lem_in.h"
#include "ft_printf.h"
/*
function attribution ID  + comptage
//input head 
// boucler until NULL // recup number of room and attribution of ID
// output nbr room
*/

int		create_id(t_list * head, t_list *start, t_list *end)
{
	int		nbr;
	t_list	*ptr;

	ptr = head;
	nbr = 2;
	while (ptr != NULL)
	{
		if (start == ptr)
			((t_room*)ptr->content)->id = 0;
		else if (end == ptr)
			((t_room*)ptr->content)->id = 1;
		else
		{
			((t_room*)ptr->content)->id = nbr;
			nbr++;
		}
		ptr = ptr->next;
	}
	return (nbr);
}


/*
function creation de matrice
// input struct avec la list des room 
//	malloc tableau de N
//	des petit tableau de N memallocer les petit tableau
//	ouput matrice char **
*/

char	**create_matrice(t_lem_in *lem_in)
{
	int nbr;
	int counter;

	counter = 0;
	nbr = create_id(lem_in->head, lem_in->start_ptr, lem_in->end_ptr);
	lem_in->rooms = nbr;
	lem_in->m_flow = (char**)ft_memalloc(sizeof(char*) * nbr);
	if (lem_in->m_flow == NULL)
		return (NULL);
	while(nbr > counter)
	{
		lem_in->m_flow[counter] = (char*)ft_memalloc(sizeof(char) * nbr);
		if (lem_in->m_flow[counter] == NULL)
		{
			free_matrice(lem_in->m_flow, counter);
			return (NULL);
		}
		counter++;
	}
	return (lem_in->m_flow);
}
