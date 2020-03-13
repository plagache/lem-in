/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:47:08 by alagache          #+#    #+#             */
/*   Updated: 2020/03/12 18:39:03 by plagache         ###   ########.fr       */
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
//	ft_printf("before parsing\n");
	if (get_ants(info) == FAILURE
		|| get_rooms(info) == FAILURE
		|| get_commands(info) == FAILURE
		|| get_links(info) == FAILURE)
		return (FAILURE);
//	ft_printf("after parsing\n");
	//validate/clean_data();
	if (create_matrice(info) == NULL)
		return (FAILURE);
//	ft_printf("matrice created\n");
	free(info->file_split);
//	ft_printf("after free\n");
	flow = edmond_karp(info);
	if (flow == -1)
		return (FAILURE);
	ft_printf("FLOW = %i\n", flow);
	path(info, flow);
	display_paths(info, flow);
	if (info->file == NULL)
		return (SUCCESS);
	return (FAILURE);
}