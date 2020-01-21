#include "lem_in.h"

int		is_command(char *str)
{
	if (ft_strcmp("##end", str) == 0 || ft_strcmp("##start", str) == 0)
		return (SUCCESS);
	return (FAILURE);
}

int		is_comment(char *str)
{
	if (str[0] == '#')
		return (SUCCESS);
	return (FAILURE);
}
