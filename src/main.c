/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#             */
/*   Updated: 2026/02/13 16:26:07 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

int	main(int argc, char **argv)
{
	t_nm	nm;
	int		res;

	ft_memset(&nm, 0, sizeof(t_nm));

	nm_parse_args(argc, argv, &nm);
	nm_process_files(&nm);

	res = nm.exit_code;
	nm_cleanup(&nm);
	
	return (res);
}
