/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:14:37 by plagache          #+#    #+#             */
/*   Updated: 2020/02/27 19:38:26 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
BFS (start, neighbours)
{
	level = 1;
	parent = NULL;
	i = 1;
	frontier = start;
	while (frontier != NULL)
	{
		next = emptylist
		for nodes in frontier
		{
			for neighbours in node
			{
				if (neighbour not in level)
				{
					level of nieghbour is i;
					parent of neighbour is node
					append neighbour to next
				}
			}
		}
		frontier is next
		i + 1;
	}
}
*/

int		check_min_path()
{
	//check if start and end has link to any room (non empty neighbours_list for start and end)
}
