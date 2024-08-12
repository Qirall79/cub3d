/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumni <zmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:52:37 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/12 13:43:33 by zmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_empty_line(t_tools *itms)
{
	int	i;
	int	j;

	i = 0;
	while (itms->maps[i])
	{
		j = 0;
		while (itms->maps[i][j] && itms->maps[i][j] == '#')
			j++;
		if (itms->maps[i][j] == '\n')
			return (ft_putstr_fd("Error\nFound empty line", 2), 1);
		i++;
	}
	return (1);
}

char	*ft_strrchr(char *s, int c)
{
	int	len;

	len = ft_strlen(s) - 1;
	if ((unsigned char)c == '\0')
		return ((char *)&s[len + 1]);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)&s[len]);
		len--;
	}
	return (0);
}

int	is_empty_2(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] == '#')
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return (1);
	return (0);
}

char	*ft_strtrim(char	*s1, char	*set)
{
	char	*tmp;
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (start < ft_strlen(s1))
	{
		if (!ft_strchr(set, s1[start]))
			break ;
		start++;
	}
	end = ft_strlen(s1);
	while (end > 0)
	{
		if (!ft_strrchr(set, s1[end]))
			break ;
		end--;
	}
	tmp = ft_substr(s1, start, (end - start + 1));
	return (tmp);
}

void	skip_line(t_tools *itms)
{
	while (itms->maps[0] && is_empty_2(itms->maps[0]))
	{
		free(itms->maps[0]);
		itms->maps[0] = NULL;
		itms->maps++;
	}
}
