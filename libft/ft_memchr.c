/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 23:51:26 by isoulima          #+#    #+#             */
/*   Updated: 2025/10/17 21:59:03 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmps;

	tmps = (unsigned char *)s;
	while (n--)
	{
		if (*tmps == (unsigned char)c)
			return ((void *)tmps);
		tmps++;
	}
	return (0);
}
