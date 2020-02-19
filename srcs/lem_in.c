#include "lem_in.h"

int main(void)
{
	t_lem_in	info;
	int	ret;

	ret = master(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
