/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:51:59 by alagache          #+#    #+#             */
/*   Updated: 2020/05/07 18:18:35 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int	read_content(int len, char *read, char *to_free)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (read[i] <= 0)
		{
			free(to_free);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	split_file(t_lem_in *info)
{
	info->file_split = ft_strsplit(info->file, '\n');
	if (info->file_split == NULL)
	{
		free(info->file);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	empty_line(char **str)
{
	char *ptr;
	char *new_str;

	ptr = ft_strstr(*str, "\n\n");
	if (ptr == NULL)
		return (SUCCESS);
	new_str = ft_strsub(*str, 0, (ptr - *str + 1));
	if (new_str == NULL)
	{
		free(*str);
		return (FAILURE);
	}
	free(*str);
	*str = new_str;
	return (SUCCESS);
}

int	read_file(t_lem_in *info)
{
	int		ret;
	char	arr[BUFF_SIZE + 1];

	info->file = ft_strnew(0);
	if (info->file == NULL)
		return (MALLOC_FAILURE);
	while ((ret = read(0, arr, BUFF_SIZE)) > 0)
	{
		arr[ret] = '\0';
		if (read_content(ret, arr, info->file) == FAILURE)
			return (FAILURE);
		info->file = ft_strjoinfree(1, info->file, arr);
		if (info->file == NULL)
			return (MALLOC_FAILURE);
	}
	if (ret == -1 || (ret == 0 && *(info->file) == '\0'))
	{
		free(info->file);
		return (FAILURE);
	}
	if (empty_line(&(info->file)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
