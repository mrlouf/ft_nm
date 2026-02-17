/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:14:12 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/17 14:23:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static int symbol_should_be_skipped(t_symbol *sym, unsigned char flags)
{
/* 	if (sym->type == 't')
		return 0; */
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

static void print_values(t_file *file, t_symbol *sym)
{	
	if (sym->value != 0 || sym->type == 'T' || sym->type == 't') {
		
 		if (file->elf_class == ELFCLASS32)
			printf("%08lx", sym->value);
		else if (file->elf_class == ELFCLASS64)
			printf("%016lx", sym->value);
		fflush(stdout);

	}
	else if (sym->type == 'a' || sym->type == 'N') {

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
