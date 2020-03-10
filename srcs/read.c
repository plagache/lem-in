/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:51:59 by alagache          #+#    #+#             */
/*   Updated: 2020/02/27 16:52:01 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int	split_file(t_lem_in *info)
{
	info->file_split = ft_strsplit(info->file, '\n');
	if (info->file_split != NULL)
		return (SUCCESS);
	return (FAILURE);
}

int	read_file(t_lem_in *info)
{
	int		ret;
	char	tab[BUFF_SIZE + 1];

	ft_memset(info, 0, sizeof(t_lem_in));
	info->file = ft_strnew(0);
	if (info->file == NULL)
		return (STRNEW_FAILURE);
	while ((ret = read(0, tab, BUFF_SIZE)) > 0)
	{
		tab[ret] = '\0';
		info->file = ft_strjoinfree(1, info->file, tab);
		if (info->file == NULL)
			return (STRJOIN_FAILURE);
	}
	if (ret == 0)
		return (SUCCESS);
	return (FAILURE);
}

int	master(t_lem_in *info)
{
	int	flow;

	read_file(info);
	split_file(info);
	free(info->file);
	ft_printf("before parsing\n");
	if (get_ants(info) == FAILURE
		|| get_rooms(info) == FAILURE
		|| get_commands(info) == FAILURE
		|| get_links(info) == FAILURE)
		return (FAILURE);
	ft_printf("after parsing\n");
	//validate/clean_data();
	if (create_matrice(info) == NULL)
		return (FAILURE);
	ft_printf("matrice created\n");
	free(info->file_split);
	ft_printf("after free\n");
	flow = edmond_karp(info);
	if (flow == -1)
		return (FAILURE);
	ft_printf("FLOW = %i\n", flow);
	if (info->file == NULL)
		return (SUCCESS);
	return (FAILURE);
}
