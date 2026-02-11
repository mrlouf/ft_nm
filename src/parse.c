/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:08:09 by nponchon          #+#    #+#             */
/*   Updated: 2026/02/11 15:00:55 by nicolas          ###   ########.fr       */
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
	int	i, total_flags;

	i = 1;
	total_flags = 0;
	while (i < argc && argv[i][0] == '-')
	{
		if (ft_strcmp(argv[i], "-a") == 0 
		|| ft_strchr(argv[i], 'a') != NULL 
		|| ft_strcmp(argv[i], "--all") == 0) {
			nm->flags |= 0x01; // Display all symbols, even debugger-only symbols
			total_flags++;
		}
		else if (ft_strcmp(argv[i], "-g") == 0 
		|| ft_strchr(argv[i], 'g') != NULL 
		|| ft_strcmp(argv[i], "--extern-only") == 0) {
			nm->flags |= 0x02; // Only external symbols
			total_flags++;
		}
		else if (ft_strcmp(argv[i], "-u") == 0
		|| ft_strchr(argv[i], 'u') != NULL 
		|| ft_strcmp(argv[i], "--undefined-only") == 0) {
			nm->flags |= 0x04; // Sort by address
			total_flags++;
		}
		else if (ft_strcmp(argv[i], "-r") == 0 
		|| ft_strchr(argv[i], 'r') != NULL 
		|| ft_strcmp(argv[i], "--reverse") == 0) {
			nm->flags |= 0x08; // Sort in reverse order
			total_flags++;
		}
		else if (ft_strcmp(argv[i], "-p") == 0 
		|| ft_strchr(argv[i], 'p') != NULL 
		|| ft_strcmp(argv[i], "--no-sort") == 0) {
			nm->flags |= 0x10; // Do not sort
			total_flags++;
		}
		else
		{
			ft_putstr_fd("ft_nm: invalid option -- '", 2);
			ft_putstr_fd(argv[i] + 1, 2);
			ft_putendl_fd("'", 2);
			print_usage();
		}
		i++;
	}
	nm->file_count = argc - total_flags - 1;
	ft_printf("[DEBUG] Number of flags: %d\n", total_flags);
	ft_printf("[DEBUG] Number of files to process: %d\n", nm->file_count);
}

static void	parse_files(int argc, char **argv, t_nm *nm)
{
	nm->files = malloc(sizeof(t_file) * (nm->file_count + 1));
	if (!nm->files)
	{
		ft_putstr_fd("ft_nm: memory allocation failed\n", 2);
		exit(1);
	}
	ft_bzero(nm->files, sizeof(t_file) * (nm->file_count + 1));

	int i = 0;
	while (i < nm->file_count)
	{
		nm->files[i].filename = argv[argc - nm->file_count + i];
		ft_printf("[DEBUG] Parsed file: %s\n", nm->files[i].filename);
		i++;
	}
	nm->files[i].filename = NULL;
}

int	nm_parse_args(int argc, char **argv, t_nm *nm)
{
	parse_flags(argc, argv, nm);
	parse_files(argc, argv, nm);

	return (0);
}