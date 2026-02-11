/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:05:55 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/11 14:56:13 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

int	nm_process_files(t_nm *nm)
{
/* 	int			fd;
	struct stat	st;

	nm.filename = (char *)filename;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd((char *)filename, 2);
		ft_putendl_fd(": No such file", 2);
		return (1);
	}

	if (fstat(fd, &st) < 0)
	{
		close(fd);
		nm_error("fstat failed");
	}

	nm.file_size = st.st_size;
	nm.file_data = mmap(NULL, nm.file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	if (nm.file_data == MAP_FAILED)
		nm_error("mmap failed");

	if (nm_parse_elf(&nm) == 0)
		nm_print_symbols(&nm);

	nm_cleanup(&nm); */
	int	fd;
    int i;

    i = 0;
    while (nm->files[i].filename != NULL)
    {
        ft_printf("[DEBUG] Processing file: %s\n", nm->files[i].filename);
        fd = open(nm->files[i].filename, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("ft_nm: ", 2);
			ft_putstr_fd(nm->files[i].filename, 2);
			ft_putendl_fd(": No such file", 2);
			nm->exit_code = 1;
			i++;
			continue;
		}
		close(fd);
		i++;
	}

	return (nm->exit_code);
}