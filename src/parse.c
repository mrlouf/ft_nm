/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:08:09 by nponchon          #+#    #+#             */
/*   Updated: 2026/02/10 16:54:30 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

int	nm_parse_args(int argc, char **argv, t_nm nm)
{
	int	i;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		if (ft_strcmp(argv[i], "-a") == 0)
			nm.flags |= 0x01; // Display all symbols, even debugger-only symbols
		else if (ft_strcmp(argv[i], "-g") == 0)
			nm.flags |= 0x02; // Only external symbols
		else if (ft_strcmp(argv[i], "-u") == 0)
			nm.flags |= 0x04; // Sort by address
		else if (ft_strcmp(argv[i], "-r") == 0)
			nm.flags |= 0x08; // Sort in reverse order
		else if (ft_strcmp(argv[i], "-p") == 0)
			nm.flags |= 0x10; // Do not sort
		else
		{
			ft_putstr_fd("ft_nm: invalid option -- '", 2);
			ft_putstr_fd(argv[i] + 1, 2);
			ft_putendl_fd("'", 2);
			exit(1);
		}
		i++;
	}
	return (0);
}