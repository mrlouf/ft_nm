/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#             */
/*   Updated: 2026/02/17 11:09:37 by nicolas          ###   ########.fr       */
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
# include <errno.h>

# include "../libft/libft.h"

# define YELLOW "\033[33m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

# define DEFAULT_FILENAME "a.out"

# define FLAG_A 0x01 // Display all symbols, even debugger-only symbols
# define FLAG_G 0x02 // Only external symbols
# define FLAG_U 0x04 // Undefined symbols only
# define FLAG_R 0x08 // Sort in reverse order
# define FLAG_P 0x10 // Do not sort: display in symbol table order

/*
** Data structures for nm
*/

typedef struct s_symbol {

    uint64_t        value;
    char            type;
    char            *name;

	// Optionalfields for sorting and printing
	uint64_t    	size;
    unsigned char 	bind;
    unsigned char 	sym_type;
	
    struct s_symbol *next;

}	t_symbol;

typedef struct s_symbol_node {
    t_symbol            symbol;
    struct s_symbol_node *next;
}	t_symbol_node;

typedef struct s_symbol_list {
    t_symbol_node   *head;
    size_t          count;
}	t_symbol_list;

typedef struct s_file_32 {
	Elf32_Ehdr		*ehdr;
	Elf32_Shdr		*shdr;
	Elf32_Sym		*symtab;
	
	char			*strtab;
	int				symtab_size;
}	t_file_32;

typedef struct s_file_64 {
	Elf64_Ehdr		*ehdr;
	Elf64_Shdr		*shdr;
	Elf64_Sym		*symtab;
	
	char			*strtab;
	int				symtab_size;
}	t_file_64;

typedef union u_file_data {
	t_file_32		file32;
	t_file_64		file64;
}	t_file_data;

typedef struct s_file
{
	char	*filename;
	void	*data;
	size_t	size;

	unsigned char	elf_class;
	t_file_data		u;

	t_symbol_list	symbols;
	
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

void	nm_parse_args(int argc, char **argv, t_nm *nm);
void	nm_process_files(t_nm *nm);
void	sort_symbols(t_symbol_list *list, unsigned char flags);
void	nm_print_symbols(t_nm *nm);
int		check_elf_magic(t_file *file);

void	nm_error(const char *msg);
void	nm_warning(const char *msg, const char *detail);

void	nm_unmap_file(t_file *file);
void	nm_cleanup(t_nm *nm);

// Symbol list management


#endif
