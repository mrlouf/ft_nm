/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:00:09 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/19 10:05:07 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

int		nm_strcasecmp(const char *s1, const char *s2)
{
    unsigned char	c1;
    unsigned char	c2;

    while (*s1 && *s2)
    {
        c1 = (unsigned char)ft_toupper(*s1);
        c2 = (unsigned char)ft_toupper(*s2);
		// Treat underscores and dots as equivalent like GNU nm seems to be doing
        if ((c1 == '.' || c1 == '_') && (c2 == '.' || c2 == '_'))
        {
            s1++;
            s2++;
            continue;
        }
        if (c1 != c2)
            return (c1 - c2);
        s1++;
        s2++;
    }
    return ((unsigned char)ft_toupper(*s1) - (unsigned char)ft_toupper(*s2));
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
	ft_putstr_fd(RESET, 2);
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