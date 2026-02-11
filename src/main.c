/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#             */
/*   Updated: 2026/02/11 14:33:09 by nicolas          ###   ########.fr       */
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
	(void)nm;
/* 	if (nm->file_data)
		munmap(nm->file_data, nm->file_size); */
}

int	nm_parse_elf(t_nm *nm)
{
	(void)nm;
/* 	nm->ehdr = (Elf64_Ehdr *)nm->file_data;

	if (nm->ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
		nm->ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
		nm->ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
		nm->ehdr->e_ident[EI_MAG3] != ELFMAG3)
	{
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(nm->filename, 2);
		ft_putendl_fd(": file format not recognized", 2);
		return (1);
	}

	ft_printf("ELF file detected: %s\n", nm->filename);
	ft_printf("Entry point: 0x%lx\n", nm->ehdr->e_entry); */

	return (0);
}

void	nm_print_symbols(t_nm *nm)
{
	(void)nm;
	ft_printf("Symbol table printing not yet implemented\n");
}


int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putendl_fd("Usage: ft_nm <file> [files...]", 2);
		return (1);
	}

	t_nm	nm;
	ft_memset(&nm, 0, sizeof(t_nm));

	nm_parse_args(argc, argv, &nm);
	nm_process_files(&nm);
	
	return (nm.exit_code);
}
