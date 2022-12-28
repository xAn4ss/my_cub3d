/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:33:52 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/25 19:47:01 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

char	*gett(int fd, char *str)
{
	char	*buffer;
	int		check;

	check = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (0);
	while (!ft_strchr(buffer, '\n') && check != 0)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
		{
			free(buffer);
			return (0);
		}
		if (check != 0)
			str = ft_strjoin1(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*getl(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!*str)
		return (0);
	while (*(str + i) != '\n' && *(str + i) != 0)
		i++;
	if (*(str + i) == '\n')
		i++;
	line = malloc(i + 1);
	ft_strlcpy(line, str, i + 1);
	return (line);
}

char	*new_str(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(str + i) != '\n' && *(str + i))
		i++;
	if (*(str + i) == 0)
	{
		free(str);
		return (NULL);
	}
	i++;
	new = ft_calloc(ft_strlen(str + i) + 1, 1);
	while (*(str + i))
		*(new + j++) = *(str + i++);
	free(str);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = gett(fd, str);
	if (!str)
		return (NULL);
	line = getl(str);
	str = new_str(str);
	return (line);
}
