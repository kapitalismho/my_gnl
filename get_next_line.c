/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salee <salee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 03:58:38 by salee             #+#    #+#             */
/*   Updated: 2021/07/19 03:58:38 by salee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*my_strcat(char *dest, char *src, char *src2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (src2[j] != '\0')
	{
		dest[i] = src2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strjoin_for_gnl(char *s1, char *s2)
{
	char	*joined_string;
	size_t	size;

	if (BUFFER_SIZE == 1)
	{
		size = 0;
		while (1)
		{
			if (s1[size++] == 0)
				break ;
		}
		size += 2;
	}
	else
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_string = malloc(size);
	if (joined_string == NULL)
	{
		free(s1);
		return (NULL);
	}
	joined_string = my_strcat(joined_string, s1, s2);
	free(s1);
	return (joined_string);
}

static char	*read_next_line(int fd, char *staticbuffer)
{
	char	*buffer;
	int		read_ret_value;

	read_ret_value = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(staticbuffer, '\n') == NULL && read_ret_value != 0)
	{
		read_ret_value = read(fd, buffer, BUFFER_SIZE);
		if (read_ret_value < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_ret_value] = '\0';
		if (staticbuffer == NULL)
			staticbuffer = ft_strdup(buffer);
		else
			staticbuffer = ft_strjoin_for_gnl(staticbuffer, buffer);
	}
	free(buffer);
	return (staticbuffer);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*idx_calculated_string;
	char	*substring;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s_len <= start)
		return (NULL);
	if (s_len < len)
		len = s_len;
	i = 0;
	idx_calculated_string = (char *)s + start;
	substring = malloc(len + 1);
	if (substring == NULL)
		return (NULL);
	while (i < len && idx_calculated_string[i] != 0)
	{
		substring[i] = idx_calculated_string[i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	*get_next_line(int fd)
{
	static char	*staticbuffer;
	char		*new_line;
	char		*old_static_buffer;
	int			new_line_index;
	int			new_staticbuf_len;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	staticbuffer = read_next_line(fd, staticbuffer);
	if (staticbuffer == NULL)
		return (NULL);
	new_line_index = (ft_strchr(staticbuffer, '\n') - staticbuffer) + 1;
	if (new_line_index < 0)
		new_line_index = ft_strlen(staticbuffer);
	new_line = ft_substr(staticbuffer, 0, new_line_index);
	new_staticbuf_len = ft_strlen(staticbuffer + new_line_index);
	old_static_buffer = staticbuffer;
	staticbuffer = ft_substr(staticbuffer, new_line_index, new_staticbuf_len);
	free(old_static_buffer);
	return (new_line);
}
