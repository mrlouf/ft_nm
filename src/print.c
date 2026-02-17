/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:14:12 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/17 18:21:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

void	nm_print_usage(void)
{
	ft_putstr_fd("Usage: ft_nm [options] <file>...\n", 2);
	ft_putstr_fd("Options:\n", 2);
	ft_putstr_fd("  -a, --debug-syms	Display all symbols, even debugger-only symbols\n", 2);
	ft_putstr_fd("  -g, --extern-only  	Only external symbols\n", 2);
	ft_putstr_fd("  -u, --undefined-only	Only undefined symbols\n", 2);
	ft_putstr_fd("  -r, --reverse-sort    Sort in reverse order\n", 2);
	ft_putstr_fd("  -p, --no-sort       	Do not sort\n", 2);
	exit(1);
}

static int symbol_should_be_skipped(t_symbol *sym, unsigned char flags)
{
	if (sym->type == 'U' && sym->name[0] == '\0')
		return 1; // Skip symbols with null name
	if (!(flags & FLAG_A) && (sym->type == 'a' || sym->type == 'N'))
		return 1; // Skip debugger-only symbols if -a is not set
	if (flags & FLAG_U && sym->type != 'U' && sym->type != 'w')
		return 1; // Only allow undefined symbols if -u is set
	if (flags & FLAG_G && !(sym->bind == STB_GLOBAL || sym->bind == STB_WEAK))
		return 1;
	
	return 0;
}

static void print_address(t_file *file, t_symbol *sym)
{
    char value[17] = { 0 };
    ft_memset(value, '0', 16);
    value[16] = '\0';

    int i = 0;
    int tmp_value = sym->value;
    while (i < 16 && sym->value != 0) {
        value[15 - i] = "0123456789abcdef"[tmp_value % 16];
        tmp_value /= 16;
        i++;
    }

    if (file->elf_class == ELFCLASS32) {
        ft_printf("%s", value + 8);
    }
    else if (file->elf_class == ELFCLASS64) {
        ft_printf("%s", value);
    }

}

static void print_values(t_file *file, t_symbol *sym)
{	
	if (sym->value != 0 || sym->type == 'T' || sym->type == 't') {
        
 		print_address(file, sym);
        
	}
	else if (sym->type == 'a' || sym->type == 'N' || sym->type == 'r' ) {

		if (file->elf_class == ELFCLASS32)
			ft_printf("%s", ZERO_PADDING_32);
		else if (file->elf_class == ELFCLASS64)
			ft_printf("%s", ZERO_PADDING_64);
        
	}
	else {

		if (file->elf_class == ELFCLASS32)
			ft_printf("%s", SPACE_PADDING_32);
		else if (file->elf_class == ELFCLASS64)
			ft_printf("%s", SPACE_PADDING_64);

	}

	ft_printf(" %c %s\n", sym->type, sym->name);
}

void nm_print_symbols(t_file *file, unsigned char flags)
{
	t_symbol_node *current = file->symbols.head;

	while (current != NULL) {

		t_symbol *sym = &current->symbol;

		if (!symbol_should_be_skipped(sym, flags))
		{
			print_values(file, sym);
		}
		current = current->next;
	}
}
