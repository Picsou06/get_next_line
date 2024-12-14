/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdalmas <evdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:29:04 by evdalmas          #+#    #+#             */
/*   Updated: 2024/12/14 21:50:52 by evdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *returned_line(char *line)
{
    if (line == NULL)
    {
        free(line);
        return (NULL);
    }
    return (line);
}

char	*get_next_line(int fd)
{
    static char*	buffer;
    char*	line;
    int		i;
    int		bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    if (buffer == NULL)
    {
        buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (buffer == NULL)
            return (NULL);
        buffer[0] = '\0';
    }

    bytes_read = 0;
    if (ft_strlen(buffer) == 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        buffer[bytes_read] = '\0';
    }

    while (bytes_read > 0)
    {
        i = 0;
        while (buffer[i] && buffer[i] != '\n')
            i++;
        if (buffer[i] == '\n')
        {
            line = ft_strjoin(line, buffer, i);
            buffer = ft_substr(buffer, i + 1, ft_strlen(buffer) - i - 1);
            return (returned_line(line));
        }
        line = ft_strjoin(line, buffer, ft_strlen(buffer));
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            buffer = NULL;
            free(line);
            return (returned_line(line));
        }
        buffer[bytes_read] = '\0';
    }
    return (returned_line(line));
}
