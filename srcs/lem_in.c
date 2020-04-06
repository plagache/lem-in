/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:47:08 by alagache          #+#    #+#             */
/*   Updated: 2020/03/18 07:38:12 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int	main(void)
{
	t_lem_in	info;
	int			ret;

	ret = master(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	master(t_lem_in *info)
{
	int	flow;

	read_file(info);
	split_file(info);
	free(info->file);
	if (get_ants(info) == FAILURE
		|| get_rooms(info) == FAILURE
		|| get_commands(info) == FAILURE
		|| get_links(info) == FAILURE)
		return (FAILURE);
	//validate/clean_data();
	if (create_matrice(info) == NULL)
		return (FAILURE);
	free_arr((void**)info->file_split);
	flow = edmond_karp(info);
	if (flow == 0)
		return (FAILURE);
	//ft_printf("FLOW = %i\n", flow);
	path(info, &flow);
	//FREE EVERYTHING
	free_paths(info->paths, flow);
	free_graph(info->head);
	free_matrice(info->m_flow, info->rooms);
	if (info->file == NULL)
		return (SUCCESS);
	return (FAILURE);
}
