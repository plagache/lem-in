/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 15:02:28 by plagache          #+#    #+#             */
/*   Updated: 2020/04/14 15:02:48 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

int		get_ants(t_lem_in *info)
{
	int			line;
	int			c;
	long long	ret;

	c = 0;
	line = 0;
	while (info->file_split[line] != NULL
			&& is_room(info->file_split[line]) == FAILURE
			&& is_command(info->file_split[line]) == FAILURE
			&& is_comment(info->file_split[line]) == SUCCESS)
		line++;
	if (info->file_split[line] == NULL)
		return (FAILURE);
	while (ft_isdigit(info->file_split[line][c]) == TRUE)
		c++;
	if (info->file_split[line][c] != '\0')
		return (FAILURE);
	info->line_ants = line;
	if ((ret = ft_atol(info->file_split[line])) > (long long)INT_MAX)
		return (FAILURE);
	info->nbr_ants = (int)ret;
	info->line = line + 1;
	return (SUCCESS);
}
