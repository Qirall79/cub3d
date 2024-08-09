/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumni <zmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:08:41 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/08 16:17:34 by zmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

static int	count_word(char *str, char c)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			cp++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (cp);
}

char	**free_2d(char **tbl)
{
	int	k;

	k = 0;
	while (tbl && tbl[k])
	{
		free(tbl[k]);
		k++;
	}
	free (tbl);
	return (tbl);
}

static void	skip_char(char	**str, char c, int *j, int i)
{
	while ((*str)[i] && (*str)[i] == c)
		(*str)++;
	(*j) = 0;
	while ((*str)[i] && (*str)[i] != c)
	{
		i++;
		(*j)++;
	}
}

char	**ft_split(char *str, char c)
{
	int		i;
	int		cp;
	int		j;
	char	**tbl;
	int		k;

	k = 0;
	i = 0;
	if (!str)
		return (NULL);
	cp = count_word(str, c);
	tbl = malloc(sizeof(char *) * (cp + 1));
	if (!tbl)
		return (NULL);
	while (cp-- > 0 && str[i])
	{
		skip_char(&str, c, &j, i);
		tbl[k] = (char *)malloc(j + 1);
		if (tbl[k] == 0)
			return (free_2d(tbl), NULL);
		ft_strlcpy(tbl[k++], str, j + 1);
		str += j;
		i = 0;
	}
	return (tbl[k] = NULL, tbl);
}
