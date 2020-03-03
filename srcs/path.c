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
** input start
** output start or NULL if error
** visit all vertices with positive capacity
*/


int		breadth_first_search(t_list *start_ptr)
{
	int		levels;
	t_list	*frontier;
	t_list	*front_ptr;
	t_list	*next_l;
	t_list	*neigh_ptr;

	levels = 1;
	frontier = start_ptr;
	while (frontier != NULL)
	{
		next_l = NULL;
		front_ptr = frontier;
		while(front_ptr != NULL) 
		{
			neigh_ptr = (t_room*)(front_ptr->content)->neighbours;
			while (neigh_ptr != NULL)
			{
				if ((t_room*)(neigh_ptr->content)->level == 0)
				{
					(t_room*)(neigh_ptr->content)->level = levels;
					(t_room*)(neigh_ptr->content)->parent = front_ptr;

					if (new_link(&next_l, (t_room*)(neigh_ptr->content)) == FAILURE)
					{
						free(next_l);
						free(frontier);
						return (NULL);
					}
					
					//if (free next & frontier && return NULL) 
				}
				neigh_ptr = neigh_ptr->next;
			}
			front_ptr = front_ptr->next;
		}
		free(frontier);
		frontier = next_l;
		levels++;
	}
	return (SUCCESS);
}

/*
** get_path
** input end
** output Path or NULL if error
** create path and returns it
*/

t_list	*get_path(t_room *end)
{

}

int		check_min_path()
{
	//check if start and end has link to any room (non empty neighbours_list for start and end)
}
