/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 14:16:27 by plagache          #+#    #+#             */
/*   Updated: 2020/04/14 14:29:41 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

/*
** //ft_printf("path that collided at |%i|",
**		((t_room*)ptr_little->content)->id);
*/

int		has_collision(t_path *little, t_path *big)
{
	t_list *ptr_little;
	t_list *ptr_big;

	ptr_little = (little->list)->next;
	while (((t_room*)ptr_little->content)->id != 0)
	{
		ptr_big = (big->list)->next;
		while (((t_room*)ptr_big->content)->id != 0)
		{
			if (((t_room*)ptr_big->content)->id
				== ((t_room*)ptr_little->content)->id)
			{
				return (TRUE);
			}
			ptr_big = ptr_big->next;
		}
		ptr_little = ptr_little->next;
	}
	return (FALSE);
}

int		remove_collision(t_path *paths, int flow)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = flow;
	while (i + 1 < flow)
	{
		j = i + 1;
		while (j < flow)
		{
			if (paths[j].len != -1 && paths[i].len != -1
				&& has_collision(paths + i, paths + j) == TRUE)
			{
				paths[j].len = -1;
				len--;
			}
			j++;
		}
		i++;
	}
	return (len);
}

void	copy_paths(t_path *new, t_path *old, int old_len)
{
	int	n;
	int	o;

	n = 0;
	o = 0;
	while (o < old_len)
	{
		if (old[o].len == -1)
			free_list(old[o].list);
		else
		{
			new[n] = old[o];
			n++;
		}
		o++;
	}
}

int		check_collision(t_path **paths, int *flow)
{
	t_path	*new;
	int		len;

	len = remove_collision(*paths, *flow);
	if (len == *flow)
		return (SUCCESS);
	new = create_path_array(len);
	if (new == NULL)
		return (FAILURE);
	copy_paths(new, *paths, *flow);
	free(*paths);
	*paths = new;
	*flow = len;
	return (SUCCESS);
}
