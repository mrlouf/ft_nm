/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#             */
/*   Updated: 2026/02/10 16:59:16 by nponchon         ###   ########.fr       */
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

typedef struct s_nm
{
	char			*filename;
	void			*file_data;
	size_t			file_size;
	Elf64_Ehdr		*ehdr;
	Elf64_Shdr		*shdr;
	Elf64_Sym		*symtab;
	char			*strtab;
	int				symtab_size;

	unsigned char	flags;
	unsigned char	exit_code;
}	t_nm;

/*
** Function prototypes
*/

int		nm_parse_args(int argc, char **argv, t_nm nm);
int		nm_parse_elf(t_nm *nm);
void	nm_print_symbols(t_nm *nm);
void	nm_error(const char *msg);
void	nm_cleanup(t_nm *nm);

#endif
