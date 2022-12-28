/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:34:13 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/25 19:46:27 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (*(s + i) == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	res = malloc(count * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}

char	*ft_strjoin1(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 || !s2)
		return (0);
	res = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!res)
		return (NULL);
	while (*(s1 + ++i))
		*(res + i) = *(s1 + i);
	j = i;
	i = 0;
	while (*(s2 + i))
		*(res + j++) = *(s2 + i++);
	free((void *)s1);
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && *(src + i))
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	return (ft_strlen (src));
}
