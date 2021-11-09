/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:16:41 by rchampli          #+#    #+#             */
/*   Updated: 2021/11/09 12:17:55 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s, int mode)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (mode == 1)
	{
		while (s[i] != '\0' && s[i] != '\n')
			i++;
	}
	else
	{
		while (s[i] != '\0')
			i++;
	}
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*b;

	i = 0;
	b = (unsigned char *)s;
	while (i < n)
		b[i++] = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*new;

	new = (char *)malloc(size * nmemb);
	if (!new)
		return (0);
	return (ft_memset(new, 0, size * nmemb));
}

static char	*ft_alloc(size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	size = size + 1;
	s = ft_calloc(sizeof(char), size);
	if (!s)
		return (0);
	while (s[i])
		i++;
	s[i] = '\0';
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

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(s1, 0) + ft_strlen(s2, 0);
	str = ft_calloc(sizeof(char), len + 1);
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
	return (str);
}

char	*ft_strdup(const char *s)
{
	unsigned int	i;
	unsigned char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(s, 0) + 1);
	if (!dest)
		return (0);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return ((char *)dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*str;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s, 0) < start)
	{
		return (ft_strdup(""));
	}
	if (ft_strlen(&s[start], 0) <= len)
		len = ft_strlen(&s[start], 0);
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
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
		buf[intbuff] = 0;
		line_tmp = line;
		line = ft_strjoin(line_tmp, buf);
		free(line_tmp);
		intbuff = read(fd, buf, BUFFER_SIZE);
	}
	line_tmp = ft_substr(line, 0, ft_strlen(line, 1));
	free(line);
	return (line);
}
