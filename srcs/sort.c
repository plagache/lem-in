/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:15:54 by alagache          #+#    #+#             */
/*   Updated: 2020/04/14 14:24:56 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Sort is OK
*/

int		is_ordered(t_room *content, t_room *to_test)
{
	if (ft_strcmp(content->room_name, to_test->room_name) <= 0)
		return (TRUE);
	return (FALSE);
}

void	content_swap(t_list *link, t_list *to_swap)
{
	void *tmp;

	tmp = link->content;
	link->content = to_swap->content;
	to_swap->content = tmp;
}

void	sort_function(t_list *head)
{
	t_list *ptr;
	t_list *tmp;

	ptr = head;
	while (ptr->next != NULL)
	{
		tmp = ptr->next;
		while (tmp != NULL)
		{
			if (is_ordered(ptr->content, tmp->content) == TRUE)
				tmp = tmp->next;
			else
				content_swap(ptr, tmp);
		}
		ptr = ptr->next;
	}
}

void	sort_paths(t_path *paths, int flow)
{
	t_path	tmp;
	int		c;
	int		d;

	c = 0;
	while (c + 1 < flow)
	{
		d = c + 1;
		while (d < flow)
		{
			if (paths[c].len > paths[d].len)
			{
				tmp = paths[c];
				paths[c] = paths[d];
				paths[d] = tmp;
			}
			else
				d++;
		}
		c++;
	}
}
