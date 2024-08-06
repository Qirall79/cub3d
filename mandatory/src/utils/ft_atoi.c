/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:40:21 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/06 11:40:44 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static unsigned long	calc_result(char *str, int sign, int i)
{
	unsigned long res;
	unsigned long old_res;
	
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		old_res = res;
		res *= 10;
		if ((res / 10) != old_res)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		res += (str[i] - 48);
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = (int) calc_result((char *)str, sign, i);
	return (result);
}
