/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 00:27:04 by isoulima          #+#    #+#             */
/*   Updated: 2025/10/09 00:46:26 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, (ft_strlen(s1)+1));
	return (ptr);
}
