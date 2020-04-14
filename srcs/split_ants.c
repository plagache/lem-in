/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 13:05:55 by plagache          #+#    #+#             */
/*   Updated: 2020/04/14 14:24:21 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

/*
**equilibrate ants
**fill rest of ants
*/

void	equilibrate_ants(int *ants, int flow, t_path *paths)
{
	int	i;
	int	j;

	i = -1;
	while (*ants > 0 && ++i + 1 < flow)
	{
		while (*ants > 0 && paths[i].len + paths[i].ants < paths[i + 1].len)
		{
			paths[i].ants++;
			*ants = *ants - 1;
			if (i > 0)
			{
				j = -1;
				while (*ants > 0 && ++j < i)
				{
					paths[j].ants++;
					*ants = *ants - 1;
				}
			}
		}
	}
}

void	fill_rest(int *ants, int flow, t_path *paths)
{
	int	nb;
	int	i;

	nb = *ants % flow;
	i = -1;
	while (++i < flow)
	{
		paths[i].ants += *ants / flow;
		if (nb > 0)
		{
			paths[i].ants++;
			nb--;
		}
	}
}

/*
** comment in function
**
**	//int i = -1;
**	//while (++i < flow)
**	//{
**	//	ft_printf("path %i will have %i ants\n", i + 1, paths[i].ants);
**	//}
*/

void	split_ants(int ants, int flow, t_path *paths)
{
	equilibrate_ants(&ants, flow, paths);
	if (ants > 0)
		fill_rest(&ants, flow, paths);
}
