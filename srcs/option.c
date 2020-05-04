/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:10:55 by plagache          #+#    #+#             */
/*   Updated: 2020/05/04 19:39:58 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int     option_check(int ac, char **av, t_lem_in *info)
{
    if (ac > 2)
    {
        ft_printf("too many arguments\n");
        ft_printf("USAGE : ./lem-in [-n]\n");
        return (FAILURE);
    }
    if (ac == 1)
        return (SUCCESS);
    if (ac == 2)
    {
        if (ft_strcmp(av[1], "-n") == 0)
            info->options ^= PRINT_LN ;
        else
        {
            ft_printf("option not recognized\n");
            ft_printf("USAGE : ./lem-in [-n]\n");
            return (FAILURE);
        }
    }
    return (SUCCESS);
}