/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:08:09 by nponchon          #+#    #+#             */
/*   Updated: 2026/02/13 17:27:31 by nponchon         ###   ########.fr       */
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
			if (argv[i][j] == 'a') {
				nm->flags |= FLAG_A; // Display all symbols, even debugger-only symbols
				nm->flags &= ~FLAG_G; // Disable extern only if display all is set
				nm->flags &= ~FLAG_U; // Disable undefined only if display all is set
			}
			else if (argv[i][j] == 'g') {
				nm->flags |= FLAG_G; // Only external symbols
				nm->flags &= ~FLAG_A; // Disable display all if extern only is set
				nm->flags &= ~FLAG_U; // Disable undefined only if extern only is set
			}
			else if (argv[i][j] == 'u') {
				nm->flags |= FLAG_U; // Undefined symbols only
				nm->flags &= ~FLAG_A; // Disable display all if undefined only is set
				nm->flags &= ~FLAG_G; // Disable extern only if undefined only is set
			}
			else if (argv[i][j] == 'r') {
				nm->flags |= FLAG_R; // Sort in reverse order
				nm->flags &= ~FLAG_P; // Disable no sort if reverse is set
			}
			else if (argv[i][j] == 'p') {
				nm->flags |= FLAG_P; // Do not sort: display in symbol table order
				nm->flags &= ~FLAG_R; // Disable reverse sort if no sort is set
			}
			else
			{
				ft_putstr_fd(RED, 2);
				ft_putstr_fd("ft_nm: invalid option -- '", 2);
				ft_putchar_fd(argv[i][j], 2);
				ft_putendl_fd("'", 2);
				ft_putstr_fd(RESET, 2);
				print_usage();
			}
			j++;
		}
		total_flags++;
		i++;
		j = 1;
	}
	nm->file_count = argc - total_flags - 1;
/* 	ft_printf("[DEBUG] Number of flags: %d\n", total_flags);
	ft_printf("[DEBUG] Number of files to process: %d\n", nm->file_count); */
}

static void	get_default_filename(t_nm *nm)
{
	nm->files = malloc(sizeof(t_file) * 2); // 1 for a.out + 1 for NULL terminator
	if (!nm->files)
		nm_error("memory allocation failed");

	ft_bzero(nm->files, sizeof(t_file) * 2);

	nm->files[0].filename = DEFAULT_FILENAME;
	nm->files[1].filename = NULL;
}

static void	parse_files(char **argv, t_nm *nm)
{
	nm->files = malloc(sizeof(t_file) * (nm->file_count + 1));
	if (!nm->files)
		nm_error("memory allocation failed");
	
	ft_bzero(nm->files, sizeof(t_file) * (nm->file_count + 1));
	
	int i = 1;
	int file_index = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-') {
			i++;
			continue;
		}
		nm->files[file_index].filename = argv[i];
		if (!nm->files[file_index].filename)
			nm_error("memory allocation failed");

		// ft_printf("[DEBUG] Parsed file: %s\n", nm->files[file_index].filename);
		i++;
		file_index++;
	}
	nm->files[file_index].filename = NULL;
}

void	nm_parse_args(int argc, char **argv, t_nm *nm)
{
	parse_flags(argc, argv, nm);

	if (nm->file_count == 0) {
		// ft_printf("%s[DEBUG] No files specified, will default to a.out%s\n", YELLOW, RESET);
		get_default_filename(nm);
	}
	else {
		// ft_printf("[DEBUG] Files to process: %d\n", nm->file_count);
		parse_files(argv, nm);
	}

}