/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:49:36 by isoulima          #+#    #+#             */
/*   Updated: 2025/10/17 21:58:49 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sign(long *n)
{
	if (*n < 0)
	{
		*n *= -1;
		return (1);
	}
	return (0);
}

static int	len(long n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	fill(char *res, long n, int len)
{
	while (n > 9)
	{
		res[len] = n % 10 + 48;
		n /= 10;
		len--;
	}
	res[len] = n % 10 + 48;
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		s;
	long	x;

	x = (long) n;
	i = 0;
	s = sign(&x);
	res = malloc(s + len(x) + 1);
	if (!res)
		return (0);
	if (s == 1)
		res[i++] = '-';
	fill(res, x, len(x) - 1 + s);
	res[len(x)+s] = 0;
	return (res);
}
