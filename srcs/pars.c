#include "lem_in.h"

int	get_ants(t_lem_in *info)
{
	int line;
	int c;

	c = 0;
	line = 0;
	while (is_command(info->file_split[line]) == FAILURE
			&& is_comment(info->file_split[line]) == SUCCESS)
	line++;
	while (ft_isdigit(info->file_split[line][c]) == TRUE)
		c++;
	if (info->file_split[line][c] != '\0')
		return (FAILURE);
	info->nbr_ants = ft_atol(info->file_split[line]);
	info->line = line + 1;
	return (SUCCESS);
}
