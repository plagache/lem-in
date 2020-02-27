/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:47:08 by alagache          #+#    #+#             */
/*   Updated: 2020/02/27 16:48:26 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	t_lem_in	info;
	int			ret;

	ret = master(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
