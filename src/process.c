/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:05:55 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/11 17:59:02 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

/* static int	nm_parse_elf(t_nm *nm)
{
	(void)nm;
	nm->ehdr = (Elf64_Ehdr *)nm->file_data;

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
	ft_printf("Entry point: 0x%lx\n", nm->ehdr->e_entry);

	return (0);
} */

static void	parse_elf_headers(t_nm *nm)
{
	(void)nm;
	ft_printf("ELF header parsing not yet implemented\n");
}

static void	extract_file_data(t_nm *nm)
{
	int	fd;
	int i;
	struct stat	st;

	i = 0;
	while (nm->files[i].filename != NULL)
	{
		ft_printf("[DEBUG] Processing file: %s\n", nm->files[i].filename);
		fd = open(nm->files[i].filename, O_RDONLY);
		if (fd < 0)
		{
			if (errno == ENOENT)
			{
				ft_putstr_fd("ft_nm: ", 2);
				ft_putstr_fd(nm->files[i].filename, 2);
				ft_putendl_fd(": No such file", 2);
			}
			else {
				ft_putstr_fd("ft_nm: error opening file: ", 2);
			}
			nm->exit_code = 1;
			i++;
			continue;
		}

		// TODO - check for file type
		if (fstat(fd, &st) < 0)
		{
			close(fd);
			nm_error("fstat failed");
		}

		if (!S_ISREG(st.st_mode))
		{
			close(fd);
			ft_printf("[DEBUG] %s: Not a regular file\n", nm->files[i].filename);
			nm->exit_code = 1;
			i++;
			continue;
		}

		nm->files[i].size = st.st_size;
		nm->files[i].data = mmap(NULL, nm->files[i].size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (nm->files[i].data == MAP_FAILED)
		{
			nm_error("mmap failed");
		}
		close(fd);
		i++;
	}
}

void nm_process_files(t_nm *nm)
{
	extract_file_data(nm);
	parse_elf_headers(nm);
}