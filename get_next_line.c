/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdalmas <evdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:29:04 by evdalmas          #+#    #+#             */
/*   Updated: 2024/12/14 21:57:10 by evdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char*	buffer;
	char*	line;
	int		i;
	int		bytes_read;

	if (!buffer)
		buffer = (char *)malloc(BUFFER_SIZE + 1);

	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
		return (NULL);

	line = (char *)malloc(1);
	line[0] = '\0';

	if (ft_strlen(buffer) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
	}
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
			{
				line = ft_strjoin(line, buffer, i);
				buffer = ft_substr(buffer, i + 1, bytes_read - i - 1);
				return (line);
			}
			i++;
		}
		line = ft_strjoin(line, buffer, bytes_read);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
	}
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
