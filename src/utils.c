/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:00:09 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/15 20:08:36 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

int	check_elf_magic(Elf64_Ehdr *ehdr)
{
	return (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
		ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
		ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
		ehdr->e_ident[EI_MAG3] != ELFMAG3);
}

void	nm_cleanup(t_nm *nm)
{
    if (!nm || !nm->files) {
        return ;
	}
 
	int i = 0;
    while (nm->files[i].filename != NULL)
    {
		t_symbol_node *current = nm->files[i].symbols.head;
		while (current != NULL) {
			t_symbol_node *tmp = current;
			current = current->next;
			free(tmp);
		}
        if (nm->files[i].data != NULL)
            munmap(nm->files[i].data, nm->files[i].size);
        i++;
    }
    free(nm->files);
}

void	nm_warning(const char *msg, const char *detail)
{
	ft_putstr_fd(YELLOW, 2);
	ft_putstr_fd("ft_nm: ", 2);
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	if (detail)
		ft_putstr_fd((char *)detail, 2);
	ft_putendl_fd("", 2);
	ft_putstr_fd(RESET, 1);
}

void	nm_error(const char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("ft_nm: ", 2);
	ft_putendl_fd((char *)msg, 2);
	ft_putstr_fd(RESET, 2);
	exit(1);
}

void    nm_unmap_file(t_file *file) {
    
    if (file->data != NULL)
    {
	    munmap(file->data, file->size);
	    file->data = NULL;
	    file->size = 0;
    }
}