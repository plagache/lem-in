/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:51:59 by alagache          #+#    #+#             */
/*   Updated: 2020/03/12 18:39:07 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int	empty_line(char *str)
{
	char *ptr;
	char *new_str;

	ptr = ft_strstr(str, "\n\n");
	if (ptr == NULL)
		return (SUCCESS);
	new_str = ft_strsub(str, 0, (ptr-str));
	if (new_str == NULL)
		return (FAILURE);
	free(str);
	str = new_str;
	return (SUCCESS);
}

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
	empty_line(info->file);
	if (ret == 0)
		return (SUCCESS);
	return (FAILURE);
}