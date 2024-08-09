/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumni <zmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:17:11 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/08 18:48:28 by zmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	int		len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == 0)
		return (0);
	return (ft_strcpy(dup, (char *)src));
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*rst;
	size_t	len;

	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	rst = (char *) malloc(len + 1);
	if (!rst)
		return (NULL);
	while (ft_strlen(s1) && s1[i])
	{
		rst[i] = s1[i];
		i++;
	}
	j = 0;
	while (ft_strlen(s2) && s2[j])
		rst[i++] = s2[j++];
	if (s1)
		free(s1);
	return (rst[i] = '\0', rst);
}

int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] == ' ')
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return (1);
	return (0);
}

int	check_extention(char *s)
{
	int	i;

	i = ft_strlen(s);
	if (i <= 4)
		return (0);
	i--;
	if (s[i] == 'b' && s[i - 1] == 'u' && s[i - 2] == 'c' && s[i - 3] == '.')
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
