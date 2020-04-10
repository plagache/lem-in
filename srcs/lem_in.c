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

int	read_ant_parse(t_lem_in *info)
{
	int	ret;

	ret = read_file(info);
	if (ret == FAILURE || ret == MALLOC_FAILURE)
	{
		ft_printf("ERROR: an error occurred while reading\n");
		return (FAILURE);
	}
	if (split_file(info) == FAILURE)
	{
		ft_printf("ERROR: an error occurred splitting the file\n");
		return (FAILURE);
	}
	if (get_ants(info) == FAILURE)
	{
		ft_printf("ERROR: no ant line found\n");
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	room_link_parse(t_lem_in *info)
{
	if (get_rooms(info) == FAILURE || info->head == NULL)
	{
		ft_printf("ERROR: an error occured parsing the rooms\n");
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	if (get_commands(info) == FAILURE)
	{
		ft_printf("ERROR: an error occured parsing the commands\n");
		free_graph(info->head, 2);
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	if (get_links(info) == FAILURE)
	{
		ft_printf("ERROR: an error occured parsing the links\n");
		free_graph(info->head, 3);
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	master(t_lem_in *info)
{
	int	flow;

	if (validate_data(info) == FAILURE)
		return (FAILURE);
	ft_printf("%s", info->file);
	free_file(info->file_split, info->file);
	return (SUCCESS);
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
	free_graph(info->head, 3);
	free_matrice(info->m_flow, info->rooms);
	if (info->file == NULL)
		return (SUCCESS);
	return (FAILURE);
}

int	main(void)
{
	t_lem_in	info;
	int			ret;

	ft_memset(&info, 0, sizeof(t_lem_in));
	ret = read_ant_parse(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	ret = room_link_parse(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	ret = master(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
