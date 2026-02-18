/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:08:09 by nponchon          #+#    #+#             */
/*   Updated: 2026/02/18 15:33:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static void invalid_option_error(char flag_char, char *flag_str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("ft_nm: invalid option -- '", 2);
	if (flag_char)
		ft_putchar_fd(flag_char, 2);
	else if (flag_str)
		ft_putstr_fd(flag_str, 2);
	ft_putendl_fd("'", 2);
	ft_putstr_fd(RESET, 1);
	nm_print_usage();
}

static void parse_short_flags(unsigned char *flags, char flag_char)
{
	if (flag_char == 'a') {
		*flags |= FLAG_A;
	}
	else if (flag_char == 'g') {
		*flags |= FLAG_G;
	}
	else if (flag_char == 'u') {
		*flags |= FLAG_U;
	}
	else if (flag_char == 'r') {
		*flags |= FLAG_R;
		*flags &= ~FLAG_P;
	}
	else if (flag_char == 'p') {
		*flags |= FLAG_P;
		*flags &= ~FLAG_R;
	}
	else
		invalid_option_error(flag_char, 0);
}

static void parse_long_flags(unsigned char *flags, char *flag_str)
{
	if (ft_strcmp(flag_str, "") == 0)
		invalid_option_error(0, flag_str);

	if (ft_strcmp(flag_str, "debug-syms") == 0) {
		*flags |= FLAG_A;
	}
	else if (ft_strcmp(flag_str, "extern-only") == 0) {
		*flags |= FLAG_G;
	}
	else if (ft_strcmp(flag_str, "undefined-only") == 0) {
		*flags |= FLAG_U;
	}
	else if (ft_strcmp(flag_str, "reverse-sort") == 0) {
		*flags |= FLAG_R;
		*flags &= ~FLAG_P;
	}
	else if (ft_strcmp(flag_str, "no-sort") == 0) {
		*flags |= FLAG_P;
		*flags &= ~FLAG_R;
	}
	else
		invalid_option_error(0, flag_str);
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
		if (argv[i][0] == '-' && argv[i][1] == '-') {
			parse_long_flags(&nm->flags, argv[i] + 2);
			total_flags++;
			i++;
			continue;
		}
		while (argv[i][j] != '\0')
		{
			parse_short_flags(&nm->flags, argv[i][j]);
			j++;
		}
		total_flags++;
		i++;
		j = 1;
	}
	nm->file_count = argc - total_flags - 1;
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

		i++;
		file_index++;
	}
	nm->files[file_index].filename = NULL;
}

void	nm_parse_args(int argc, char **argv, t_nm *nm)
{
	parse_flags(argc, argv, nm);

	if (nm->file_count == 0) {
		get_default_filename(nm);
	}
	else {
		parse_files(argv, nm);
	}

}