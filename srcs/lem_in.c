#include "lem_in.h"

int	read_file(t_lem_in *info_ptr)
{
	int		ret;
	char	tab[BUFF_SIZE + 1];

	ft_memset(info_ptr, 0, sizeof(t_lem_in));
	info_ptr->file = ft_strnew(0);
	if (info_ptr->file == NULL)
		return (STRNEW_FAILURE);
	while ((ret = read(0, tab, BUFF_SIZE)) > 0)
	{
		tab[ret] = '\0';
		info_ptr->file = ft_strjoinfree(1, info_ptr->file, tab);
		if (info_ptr->file == NULL)
			return (STRJOIN_FAILURE);
	}
	if (ret == 0)
		return (SUCCESS);
	return (FAILURE);
}

int main(void)
{
	t_lem_in	info;

	read_file(&info);
	printf("%s\n", info.file);
	free(info.file);
	return (EXIT_SUCCESS);
}
