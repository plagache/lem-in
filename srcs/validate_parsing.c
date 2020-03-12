#include "lem_in.h"
#include "ft_printf.h"


//duplicate link / room
//parse the list of room next have same name
//if ptr->content == ptr->next->content
//this is an error

int		duplicate_room(t_list *head)
{
	t_list	*ptr;

	ptr = *head;
	if (ptr->next != NULL)
	{
		if (ptr->content == ptr->next->content)
		{
			//free_list(head); free_list and t_room content
			return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (FAILURE);
}

/*
** for each room sort neighbours alphanumerically
** and remove duplicate neighbours
*/

int		duplicate_link(t_list *head)
{
	t_list	*ptr_head;
	t_list	*ptr_neigh;

	ptr_head = head;
	while (ptr_head != NULL)
	{
		ptr_neigh = ((t_room*)ptr_head->content)->neighbours;
		//sort neighbours
		//check if content and next->content are equal
		////if equal 
		//	//free next link
		//	//and rebound pointers to preserve list
		ptr_head = ptr_head->next;
	}
}

/*
** start and end has at least one links
*/
int		no_path(t_list *start, t_list *end)
{
	if (((t_room*)start->content)->neighbours == NULL
		|| ((t_room*)end->content)->neighbours == NULL)
	{
		//ERROR free everything
		return (FAILURE);
	}
	return (SUCCESS);
}

//if char command has more than 1 bit set == ERROR //start and end on a different room
int		command(t_list *start, t_list *end)
{
	if (start == end)
	{
		//ERROR
		return (FAILURE);
	}
	return (SUCCESS);
}

//if Start has End as neighbour == ERROR
int		ultimate_path(t_list *start, t_list *end)
{
	t_list	*ptr;

	ptr = ((t_room*)start->content)->neighbours;
	while (ptr != NULL)
	{
		if (ptr->content == end->content)
		{
			//ERROR
			return  (FAILURE);
		}
		ptr = ptr->next;
	}
	return (SUCCESS);
}
