/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumni <zmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:06:10 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/08 16:10:52 by zmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*ft_strchr(char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tbl;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (NULL);
	if (len >= (size_t)ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	tbl = (char *)malloc(sizeof(char) * (len + 1));
	if (!tbl)
		return (NULL);
	while (i < len)
	{
		tbl[i] = s[start];
		i++;
		start++;
	}
	tbl[len] = '\0';
	return (tbl);
}

char	*check_1(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!str)
		return (free(str), str = NULL, NULL);
	while (str[i] && str[i] != '\n')
		i++;
	s = ft_substr(str, 0, (i + 1));
	return (s);
}

char	*check_2(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!str)
		return (free(str), str = NULL, NULL);
	while (str[i] && str[i] != '\n')
		i++;
	s = ft_substr(str, (i + 1), (ft_strlen(str) - (i + 1)));
	free(str);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*sta;
	char		*rst;
	char		*buffer;
	int			len;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1)
		return (free(sta), sta = NULL, NULL);
	buffer = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buffer)
		return (free(buffer), NULL);
	len = 1;
	while (len)
	{
		if (ft_strchr(sta, '\n'))
			break ;
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1)
			return (free(sta), free(buffer), NULL);
		buffer[len] = '\0';
		sta = ft_strjoin(sta, buffer);
	}
	free(buffer);
	rst = check_1(sta);
	return (sta = check_2(sta), rst);
}
