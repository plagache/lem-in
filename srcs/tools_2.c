#include "lem_in.h"
#include "ft_printf.h"

int		path_len(t_list *path)
{
	t_list *ptr;
	int		len;
	
	len = 0;
	ptr = path;
	while(ptr != NULL)
	{
		len++;
		ptr = ptr->next;
	}
	return (len - 2);
}

int		new_link(t_list **head, t_room *room_ptr)
{
	t_room *room;
	t_list *new;

	room = room_ptr;
	if (room == NULL)
		room = (t_room*)ft_memalloc(sizeof(t_room));
	if (room == NULL)
		return (FAILURE);
	new = ft_lstnew(0, 0);
	if (new == NULL)
		return (FAILURE);
	new->content = room;
	new->content_size = sizeof(t_room);
	ft_lstadd(head, new);
	return (SUCCESS);
	/* free room if link fail*/
}
