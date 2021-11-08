/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:16:41 by rchampli          #+#    #+#             */
/*   Updated: 2021/11/08 16:33:53 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_alloc(size_t size)
{
	char	*s;

	size = size + 1;
	s = malloc(sizeof(char) * size);
	if (!s)
		return (0);
	while (*s)
		s++;
	s = '\0';
	return (s);
}

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			i;
	size_t			len;
	size_t			j;
	unsigned char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * len + 1);
	if (!str || !s1 || !s2)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return ((char *)str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*line_tmp;
	static char	buf[BUFFER_SIZE + 1];
	size_t		i;
	int			intbuff;

	i = 0;
	line = ft_alloc(0);
	if (!line || fd == -1 || BUFFER_SIZE < 1)
		return (0);
	intbuff = read(fd, buf, BUFFER_SIZE);
	while (ft_strchr((const char *)line, '\n') == 0
		&& intbuff > 0)
	{
		buf[intbuff] = '\0';
		line_tmp = line;
		line = ft_strjoin(line_tmp, buf);
		free(line_tmp);
	}
	return (line);
}
