/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#             */
/*   Updated: 2026/02/11 17:40:41 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void	nm_error(const char *msg)
{
	ft_putstr_fd("ft_nm: ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(1);
}

void	nm_cleanup(t_nm *nm)
{
	// TODO: Unmap files, free memory, etc.

	int i = 0;
	while (nm->files[i].filename != NULL)
	{
		// if (nm->files->data != NULL)
		//	munmap(nm->files->data, nm->files->size);
		i++;
	}
	free(nm->files);
}


void	nm_print_symbols(t_nm *nm)
{
	(void)nm;
	ft_printf("Symbol table printing not yet implemented\n");
}

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
