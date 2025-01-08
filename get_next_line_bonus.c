/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdalmas <evdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:29:04 by evdalmas          #+#    #+#             */
/*   Updated: 2025/01/08 13:58:33 by evdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_answer(char *line)
{
	int		i;
	char	*buffer;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (0);
	buffer = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	line[i + 1] = '\0';
	return (buffer);
}

static char	*read_and_stock(int fd, char *readed, char *buffer)
{
	int		nb_read;
	char	*temp;

	nb_read = 1;
	while (nb_read != '\0')
	{
		nb_read = read(fd, readed, BUFFER_SIZE);
		if (nb_read == -1)
			return (0);
		else if (nb_read == 0)
			break ;
		readed[nb_read] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		temp = buffer;
		buffer = ft_strjoin(temp, readed);
		free(temp);
		temp = NULL;
		if (ft_strchr(readed, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;
	char		*readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (0);
	readed = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!readed)
		return (0);
	line = read_and_stock(fd, readed, buffer[fd]);
	free(readed);
	readed = NULL;
	if (!line)
		return (NULL);
	buffer[fd] = get_answer(line);
	return (line);
}
