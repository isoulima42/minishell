/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:08:31 by isoulima          #+#    #+#             */
/*   Updated: 2025/10/17 21:59:22 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy(char *dst, const char *src, char c)
{
	size_t	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

static size_t	count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static size_t	len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**frit(char **w, size_t i)
{
	while (i > 0)
		free(w[--i]);
	free(w);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**w;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	w = malloc(sizeof(char *) * (count(s, c) + 1));
	if (!w)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			w[j] = malloc(len(s + i, c) + 1);
			if (!w[j])
				return (frit(w, j));
			copy(w[j++], s + i, c);
		}
		i++;
	}
	w[j] = 0;
	return (w);
}
