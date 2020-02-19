#include "lem_in.h"

int		is_command(char *str)
{
	if (ft_strcmp("##end", str) == 0 || ft_strcmp("##start", str) == 0)
		return (SUCCESS);
	return (FAILURE);
}

int		start_with_char(char *str, char c)
{
	if (str[0] == c)
		return (SUCCESS);
	return (FAILURE);
}

int		is_comment(char *str)
{
	if (start_with_char(str, '#') == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int		occurrence_of(char *str, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int		is_link(char *str)
{
	if (is_comment(str) == SUCCESS)
		return (FAILURE);
	if (occurrence_of(str, '-') != 1)
		return (FAILURE);
	if (ft_strchr(str, ' ') != NULL)
		return (FAILURE);
	return (SUCCESS);
}

int		mv_to_next_room(t_lem_in *info)
{
	while (is_command(info->file_split[info->line]) == SUCCESS
			|| is_comment(info->file_split[info->line]) == SUCCESS)
		info->line++;
	if (is_link(info->file_split[info->line]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int		is_room(char *str)
{
	char	*ptr;

	if (start_with_char(str, 'L') == SUCCESS)
		return (FAILURE);
	if (occurrence_of(str, ' ') != 2)
		return (FAILURE);
	ptr = ft_strchr(str, ' ') + 1;
	if (*ptr == ' ')
		return (FAILURE);
	while (ft_isdigit(*ptr) == TRUE)
		ptr++;
	if (*ptr++ != ' ')
		return (FAILURE);
	while (ft_isdigit(*ptr) == TRUE)
		ptr++;
	if (*ptr != '\0')
		return (FAILURE);
	return (SUCCESS);
}

void	free_arr(void** arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
