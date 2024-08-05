/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:08:41 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/05 22:45:04 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	exit(1);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
int ft_strncmp(char *s1, char *s2, int c)
{
	int i = 0;
	if ((int)ft_strlen(s1) < c || (int)ft_strlen(s2) < c)
		return (0);
	while (s1[i] && s2[i] && i < c)
	{
		if (s1[i] != s2[i])
			return(0);
		i++;
	}
	return(1);
}
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

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