/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:08:09 by nponchon          #+#    #+#             */
/*   Updated: 2026/02/11 16:43:54 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static void	print_usage(void)
{
	ft_putstr_fd("Usage: ft_nm [options] <file>...\n", 2);
	ft_putstr_fd("Options:\n", 2);
	ft_putstr_fd("  -a, --all           	Display all symbols, even debugger-only symbols\n", 2);
	ft_putstr_fd("  -g, --extern-only  	Only external symbols\n", 2);
	ft_putstr_fd("  -u, --undefined-only	Sort by address\n", 2);
	ft_putstr_fd("  -r, --reverse       	Sort in reverse order\n", 2);
	ft_putstr_fd("  -p, --no-sort       	Do not sort\n", 2);
	exit(1);
}

static void	parse_flags(int argc, char **argv, t_nm *nm)
{
	int	i, j, total_flags;

	i = 1;
	j = 1;
	total_flags = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-') {
			i++;
			continue;
		}
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == 'a')
				nm->flags |= 0x01; // Display all symbols, even debugger-only symbols
			else if (argv[i][j] == 'g')
				nm->flags |= 0x02; // Only external symbols
			else if (argv[i][j] == 'u')
				nm->flags |= 0x04; // Sort by address
			else if (argv[i][j] == 'r')
				nm->flags |= 0x08; // Sort in reverse order
			else if (argv[i][j] == 'p')
				nm->flags |= 0x10; // Do not sort
			else
			{
				ft_putstr_fd("ft_nm: invalid option -- '", 2);
				ft_putchar_fd(argv[i][j], 2);
				ft_putendl_fd("'", 2);
				print_usage();
			}
			j++;
		}
		total_flags++;
		i++;
		j = 1;
	}
	nm->file_count = argc - total_flags - 1;
	ft_printf("[DEBUG] Number of flags: %d\n", total_flags);
	ft_printf("[DEBUG] Number of files to process: %d\n", nm->file_count);
}

static void	get_default_filename(t_nm *nm)
{
	nm->files = malloc(sizeof(t_file) * 2); // 1 for a.out + 1 for NULL terminator
	if (!nm->files)
	{
		ft_putstr_fd("ft_nm: memory allocation failed\n", 2);
		exit(1);
	}
	ft_bzero(nm->files, sizeof(t_file) * 2);

	nm->files[0].filename = ft_strdup("a.out");
	if (!nm->files[0].filename)
	{
		ft_putstr_fd("ft_nm: memory allocation failed\n", 2);
		exit(1);
	}

	nm->files[1].filename = NULL;
}

static void	parse_files(char **argv, t_nm *nm)
{
	nm->files = malloc(sizeof(t_file) * (nm->file_count + 1));
	if (!nm->files)
	{
		ft_putstr_fd("ft_nm: memory allocation failed\n", 2);
		exit(1);
	}
	ft_bzero(nm->files, sizeof(t_file) * (nm->file_count + 1));
	
	int i = 1;
	int file_index = 0;
	while (argv[i] )
	{
		if (argv[i][0] == '-') {
			i++;
			continue;
		}
		nm->files[file_index].filename = ft_strdup(argv[i]);
		if (!nm->files[file_index].filename)
		{
			ft_putstr_fd("ft_nm: memory allocation failed\n", 2);
			exit(1);
		}
		ft_printf("[DEBUG] Parsed file: %s\n", nm->files[file_index].filename);
		i++;
		file_index++;
	}
	nm->files[file_index].filename = NULL;
}

int	nm_parse_args(int argc, char **argv, t_nm *nm)
{
	parse_flags(argc, argv, nm);

	if (nm->file_count == 0) {
		ft_printf("[DEBUG] No files specified, will default to a.out\n");
		get_default_filename(nm);
	}
	else {
		ft_printf("[DEBUG] Files to process: %d\n", nm->file_count);
		parse_files(argv, nm);
	}

	return (0);
}