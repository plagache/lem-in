#include "lem_in.h"

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

int	display_data(t_lem_in *info)
{
	int c;

	c = 0;
	while (info->file_split[c] != NULL)
	{
		printf("%s\n", info->file_split[c]);
		free(info->file_split[c]);
		c++;
	}
	printf("ants=|%lli|\n", info->nbr_ants);
	free(info->file_split);
	return (c);
}

int	master(t_lem_in *info)
{
	read_file(info);
	split_file(info);
	if (get_ants(info) == FAILURE
		|| get_rooms(info) == FAILURE
		|| get_commands(info) == FAILURE
		|| get_links(info) == FAILURE)
		return (FAILURE);
	display_data(info);
	free(info->file);
	if (info->file == NULL)
		return (SUCCESS);
	return (FAILURE);
}