/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizhang <kaizhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:06:50 by kaizhang          #+#    #+#             */
/*   Updated: 2022/07/10 22:19:30 by kaizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char **str, int nl_pos)
{
	char	*line;
	int		i;

	if (nl_pos == 0)
		nl_pos = ft_strlen(*str);
	line = malloc(nl_pos + 1);
	line[nl_pos] = '\0';
	i = 0;
	while (i < nl_pos)
	{
		line[i] = str[0][i];
		i++;
	}
	return (line);
}

char	*ft_next_line(char **str)
{
	char	*next;
	int		i;
	int		j;

	next = NULL;
	i = ft_strlen(*str) - ft_get_eol(*str);
	if (i != ft_strlen(*str) && i > 0)
	{
		next = malloc(i + 1);
		next[i++] = '\0';
		j = ft_strlen(*str);
		while (i-- > 0)
		{
			next[i] = str[0][j];
			j--;
		}		
	}
	free(*str);
	*str = next;
	return (next);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*storage[FOPEN_MAX];
	char		*line;
	int			byte_read;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX || (read(fd, 0, 0) == -1))
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	while (!ft_get_eol(&storage[fd][0]))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		storage[fd] = ft_strjoin(storage[fd], buffer);
	}
	free(buffer);
	if (!storage[fd])
		return (NULL);
	line = ft_get_line(&storage[fd], ft_get_eol(storage[fd]));
	storage[fd] = ft_next_line(&storage[fd]);
	return (line);
}
