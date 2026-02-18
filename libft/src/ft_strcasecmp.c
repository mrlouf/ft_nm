/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:32:36 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/18 14:33:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    ft_strcasecmp(const char *s1, const char *s2)
{
    unsigned char	c1;
    unsigned char	c2;

    while (*s1 && *s2)
    {
        c1 = (unsigned char)ft_toupper(*s1);
        c2 = (unsigned char)ft_toupper(*s2);
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
