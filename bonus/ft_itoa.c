/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:01:32 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/20 13:30:38 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	numb_size(int n)
{
	int	size;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	long	nb;
	char	*res;

	size = numb_size(n);
	res = (char *) malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	nb = n;
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	res[size--] = 0;
	if (!n)
		res[0] = '0';
	while (nb)
	{
		res[size--] = (nb % 10) + 48;
		nb /= 10;
	}
	return (res);
}