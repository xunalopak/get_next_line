/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:16:41 by rchampli          #+#    #+#             */
/*   Updated: 2021/11/09 17:17:09 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s, int mode)
{
	size_t	i;

	i = -1;
	if (!s)
		return (0);
	if (mode == 1)
		while (s[++i] != '\0' && s[i] != '\n')
			;
	else
		while (s[++i] != '\0')
			i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = -1;
	if (!src)
		return (0);
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
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
	char	*new;

	new = (char *)malloc(size * nmemb);
	if (!new)
		return (0);
	return (ft_memset(new, 0, size * nmemb));
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

	i = -1;
	j = -1;
	len = ft_strlen(s1, 0) + ft_strlen(s2, 0);
	str = ft_calloc(sizeof(char), len + 1);
	if (!str || !s1 || !s2)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

static char	*ft_save(char *line, size_t *i)
{
	if (ft_strchr(line, '\n'))
	{
		ft_strcpy(line, ft_strchr(line, '\n') + 1);
		return (line);
	}
	if (ft_strlen(line, 1) > 0)
	{
		ft_strcpy(line, ft_strchr(line, '\0'));
		*i = 0;
		return (line);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*line_tmp;
	static char	buf[BUFFER_SIZE + 1];
	size_t		intbuff;
	size_t		i;

	i = 1;
	line = 0;
	line = ft_calloc(0, 0);
	if (!line || fd < 0 || BUFFER_SIZE < 1)
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
	if ((ft_save(line, &i) != 0) && i == 1)
		return (line);
	return (0);
}
