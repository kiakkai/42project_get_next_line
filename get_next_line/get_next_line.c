/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizhang <kaizhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:07:11 by ktang             #+#    #+#             */
/*   Updated: 2022/08/10 17:12:17 by kaizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

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
	char			*next;
	int	i;
	int				j;

	next = NULL;
	i = ft_strlen(*str) - ft_get_eol(*str);
	if (i != ft_strlen(*str) && i > 0)
	{	
		next = malloc(i + 1);
		next[i++] = '\0';
		j = ft_strlen(*str);
		while (i-- >= 0)
		{
			printf("%i\n", i);
			next[i] = str[0][j];
			j--;
			//i = 3  0
			//i = 2  e
			//i = 1 h
			//i = 0 ?
		}		
	}
	//printf("%s\n", next);
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
	while (!ft_get_eol(storage[fd]))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		storage[fd] = ft_strjoin(storage[fd], buffer);
	}
	//printf("the storage1 is :%s", storage[fd]);
	free(buffer);
	if (!storage[fd])
		return (NULL);
	line = ft_get_line(&storage[fd], ft_get_eol(storage[fd]));
	storage[fd] = ft_next_line(&storage[fd]);
	//printf("the storage2 is :%s", storage[fd]);
	return (line);
}

int	main(void)
{
	char	*line1;
	//char	*line2;

	int	i;
	int	fd1;
	//int	fd2;

	fd1 = open("test1.txt", O_RDONLY);
	//fd2 = open("test2.txt", O_RDONLY);
	//write(fd1, "kai", 3);
	//printf("starting\n");
	//printf("%i\n", fd1);
	//printf("%i\n", fd2);
	i = 0;
	while (i >= 0)
	{
		line1 = get_next_line(fd1);
		if (line1)
		{	
			printf("%s", line1);
		}
		/*line2 = get_next_line(fd2);
		if (line2)
		{
			printf("%s\n", line2);
		}*/
		if (!line1)
		{
			break ;
		}
		free(line1);
		//free(line2);
		i++;
	}
	close(fd1);
	//close(fd2);
	return (0);
}
