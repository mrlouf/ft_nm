/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#             */
/*   Updated: 2026/02/11 14:32:09 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <elf.h>
# include "../libft/libft.h"

/*
** Data structures for nm
*/

typedef struct s_file
{
	char	*filename;
	void	*data;
	size_t	size;

	Elf64_Ehdr		*ehdr;
	Elf64_Shdr		*shdr;
	Elf64_Sym		*symtab;
	char			*strtab;
	int				symtab_size;
}	t_file;

typedef struct s_nm
{
	t_file			*files;
	int				file_count;

	unsigned char	flags;
	unsigned char	exit_code;
}	t_nm;

/*
** Function prototypes
*/

int		nm_parse_args(int argc, char **argv, t_nm *nm);
int		nm_process_files(t_nm *nm);
int		nm_parse_elf(t_nm *nm);
void	nm_print_symbols(t_nm *nm);
void	nm_error(const char *msg);
void	nm_cleanup(t_nm *nm);

#endif
