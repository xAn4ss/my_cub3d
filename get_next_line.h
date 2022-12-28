/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:02:58 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/25 19:46:36 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include<stdio.h>
# include<stdlib.h>
# include<fcntl.h>
# include<unistd.h>
# define BUFFER_SIZE 10

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin1(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*gett(int fd, char *str);
char	*getl(char *str);
char	*new_str(char *str);
char	*get_next_line(int fd);
#endif