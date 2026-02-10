/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrlouf                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#             */
/*   Updated: 2026/02/10 13:57:00 by mrlouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void	nm_error(const char *msg)
{
	ft_putstr_fd("nm: ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(1);
}

void	nm_cleanup(t_nm *nm)
{
	if (nm->file_data)
		munmap(nm->file_data, nm->file_size);
}

int	nm_parse_elf(t_nm *nm)
{
	nm->ehdr = (Elf64_Ehdr *)nm->file_data;
	
	if (nm->ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
		nm->ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
		nm->ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
		nm->ehdr->e_ident[EI_MAG3] != ELFMAG3)
	{
		ft_putstr_fd("nm: ", 2);
		ft_putstr_fd(nm->filename, 2);
		ft_putendl_fd(": file format not recognized", 2);
		return (1);
	}
	
	ft_printf("ELF file detected: %s\n", nm->filename);
	ft_printf("Entry point: 0x%lx\n", nm->ehdr->e_entry);
	
	return (0);
}

void	nm_print_symbols(t_nm *nm)
{
	(void)nm;
	ft_printf("Symbol table printing not yet implemented\n");
}

static int	nm_process_file(const char *filename)
{
	t_nm		nm;
	int			fd;
	struct stat	st;

	ft_memset(&nm, 0, sizeof(t_nm));
	nm.filename = (char *)filename;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("nm: ", 2);
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
	
	nm_cleanup(&nm);
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	ret;

	if (argc < 2)
	{
		ft_putendl_fd("Usage: nm <file> [files...]", 2);
		return (1);
	}
	
	ret = 0;
	i = 1;
	while (i < argc)
	{
		if (argc > 2)
			ft_printf("\n%s:\n", argv[i]);
		if (nm_process_file(argv[i]) != 0)
			ret = 1;
		i++;
	}
	
	return (ret);
}
