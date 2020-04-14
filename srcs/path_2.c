/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 14:12:59 by plagache          #+#    #+#             */
/*   Updated: 2020/04/14 15:11:33 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"
#include <limits.h>

t_path	*create_path_array(int flow)
{
	t_path	*arr;

	arr = (t_path*)ft_memalloc(sizeof(t_path) * flow);
	if (arr == NULL)
		return (NULL);
	return (arr);
}

/*
** put new into best if new has less turn
*/

void	update_best_paths(t_path_cont *best, t_path_cont *new)
{
	if (best->turns > new->turns)
	{
		if (best->turns != INT_MAX)
			free_paths(best->paths, best->flow);
		best->paths = new->paths;
		best->flow = new->flow;
		best->turns = new->turns;
	}
	else
		free_paths(new->paths, new->flow);
}
