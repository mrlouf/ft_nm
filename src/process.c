/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:05:55 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/12 13:04:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"


static int	parse_elf_headers(t_file *file)
{
	ft_putstr_fd(BLUE, 1);
	ft_printf("[DEBUG] Parsing mapping of file: %s\n", file->filename);
	ft_printf("[DEBUG] Mapped at %p\n", file->data);

	file->ehdr = (Elf64_Ehdr *)file->data;

	if (check_elf_magic(file->ehdr) != 0) {
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(file->filename, 2);
		ft_putendl_fd(": file format not recognized", 2);
		ft_putstr_fd(RESET, 1);
		return (1);
	}

	ft_printf("[DEBUG] ELF file detected: %s of type: ", file->filename);
	switch (file->ehdr->e_type) {
		case ET_REL:    // Relocatable file (.o)
			printf("Object file\n");
			break;
		case ET_EXEC:   // Executable file
			printf("Executable\n");
			break;
		case ET_DYN:    // Shared object (.so) ou PIE executable
			printf("Shared library or PIE executable\n");
			break;
		case ET_CORE:   // Core dump
			printf("Core file\n");
			break;
		default:
			fprintf(stderr, "Unknown ELF type\n");
			return (1);
	}
	
	printf("[DEBUG] Entry point: 0x%lx\n", file->ehdr->e_entry);
	ft_putstr_fd(RESET, 1);

	return (0);
}

static int	extract_file_data(t_file *file)
{
	int	fd;
	struct stat	st;

	fd = open(file->filename, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("ft_nm: ", 2);
			ft_putstr_fd(file->filename, 2);
			ft_putendl_fd(": No such file", 2);
		}
		return (1);
	}

	if (fstat(fd, &st) < 0)
	{
		close(fd);
		nm_error("fstat failed");
	}

	if (!S_ISREG(st.st_mode))	// Skip non regular files (directories, device files)
	{
		close(fd);
		ft_printf("%s[DEBUG] %s: Not a regular file%s\n", YELLOW, file->filename, RESET);
		return (1);
	}

	file->size = st.st_size;
	file->data = mmap(NULL, file->size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	
	if (file->data == MAP_FAILED)
		nm_error("mmap failed");

	return (0);
}

static void extract_symbols(t_file *file, t_nm *nm)
{
	(void)file;
	(void)nm;
	ft_printf("%s[DEBUG] Symbol extraction not yet implemented for file: %s%s\n", YELLOW, file->filename, RESET);
}

void nm_process_files(t_nm *nm)
{
	int i;

	i = 0;
	while (nm->files[i].filename != NULL)
	{
		ft_printf("%s[DEBUG] Processing file: %s%s\n", GREEN, nm->files[i].filename, RESET);
		if (extract_file_data(&nm->files[i]) != 0 || parse_elf_headers(&nm->files[i]) != 0)
		{
			nm->exit_code = 1;
			i++;
			continue;
		}

		// Process the file (e.g., extract symbol table)
		extract_symbols(&nm->files[i], nm);
		
		// Clean-up


		i++;
	}
}