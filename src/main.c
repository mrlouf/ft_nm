/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#             */
/*   Updated: 2026/02/12 13:04:37 by nicolas          ###   ########.fr       */
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
