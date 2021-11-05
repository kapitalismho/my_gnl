/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salee <salee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 03:58:41 by salee             #+#    #+#             */
/*   Updated: 2021/07/19 03:58:41 by salee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (1)
	{
		if (str[i] == 0)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, char c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0' && *s != c)
	{
		s++;
	}
	if (*s == c)
	{
		return ((char *)s);
	}
	return (NULL);
}

char	*ft_strdup(char *src)
{
	size_t	i;
	size_t	src_length;
	char	*dest;

	if (src == NULL)
		return (NULL);
	i = 0;
	src_length = ft_strlen(src);
	dest = malloc(src_length + 1);
	if (dest == NULL)
		return (NULL);
	while (i <= src_length)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
