#include "lem_in.h"
#include "ft_printf.h"

void	free_list(t_list *lst)
{
	if (lst->next != NULL)
		free_list(lst->next);
	lst->content = NULL;
	free(lst);
}
