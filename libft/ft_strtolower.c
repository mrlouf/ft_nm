/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:48:11 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/13 19:51:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char	*ft_strtolower(char *str)
{
    int i = 0;
    while (str[i]) {
        str[i] = ft_tolower(str[i]);
        i++;
    }
    return str;
}
