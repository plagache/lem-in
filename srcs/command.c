
#include "lem_in.h"
#include "ft_printf.h"

int		get_start(char **file, int line, t_lem_in *info)
{
	int		len;
	t_list	*ptr;

	while (ft_strcmp("##start", file[line]) != 0 && line + 1 < info->line)
		line++;
	if (line + 1 == info->line)
		return (FAILURE);
	while (is_room(file[line]) == FAILURE && line + 1 < info->line)
		line++;
	if (line == info->line)
		return (FAILURE);
	len = ft_strchr(file[line], ' ') - file[line];
	ptr = info->head;
	while (ptr != NULL && ft_strncmp(file[line], ((t_room*)(ptr->content))->room_name, len) != 0)
		ptr = ptr->next;
	if (ptr == NULL)
		return (FAILURE);
	((t_room*)(ptr->content))->command ^= START_COMMAND;
	((t_room*)(ptr->content))->level = -1;
	info->start_ptr = ptr;
	return (SUCCESS);
}

int		get_end(char **file, int line, t_lem_in *info)
{
	int		len;
	t_list	*ptr;

	while (ft_strcmp("##end", file[line]) != 0 && line + 1 < info->line)
		line++;
	if (line + 1 == info->line)
		return (FAILURE);
	while (is_room(file[line]) == FAILURE && line + 1 < info->line)
		line++;
	if (line == info->line)
		return (FAILURE);
	len = ft_strchr(file[line], ' ') - file[line];
	ptr = info->head;
	while (ptr != NULL && ft_strncmp(file[line], ((t_room*)(ptr->content))->room_name, len) != 0)
		ptr = ptr->next;
	if (ptr == NULL)
		return (FAILURE);
	((t_room*)(ptr->content))->command ^= END_COMMAND;
	info->end_ptr = ptr;
	return (SUCCESS);
}

int		get_commands(t_lem_in *info)
{
	sort_function(info->head);
	if (get_start(info->file_split, info->line_ants, info) == FAILURE)
		return (FAILURE);
	if (get_end(info->file_split, info->line_ants, info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
	//free list and file
}
