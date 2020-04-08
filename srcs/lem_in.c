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
#include <limits.h>

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
	//print_farm(info->file_split);
	free_arr((void**)info->file_split);
	info->best_paths.turns = INT_MAX;
	flow = edmond_karp(info);
	if (flow == 0 || flow == FAILURE)
		return (FAILURE);
	//path(info, &flow);
	//display_paths(info->best_paths.paths, info->best_paths.flow);
	move_paths(info->best_paths.flow, info->best_paths.paths);
	//FREE EVERYTHING
	free_paths(info->best_paths.paths, info->best_paths.flow);
	free_graph(info->head);
	free_matrice(info->m_flow, info->rooms);
	if (info->file == NULL)
		return (SUCCESS);
	return (FAILURE);
}
