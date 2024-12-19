/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdalmas <evdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:29:04 by evdalmas          #+#    #+#             */
/*   Updated: 2024/12/19 10:09:17 by evdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static char*	buffer = NULL;
    char*	line;
    int		i;  
    int		bytes_read;

    if (!buffer)
    {
        buffer = (char *)malloc(BUFFER_SIZE + 1);
        if (buffer)
            buffer[0] = '\0';
    }

    if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
        return (NULL);

    line = (char *)malloc(1);
    if (!line)
    {
        free(buffer);
        return (NULL);
    }
    line[0] = '\0';

    if (ft_strlen(buffer) == 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            free(buffer);
            buffer = NULL;
            free(line);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
    }
    while (bytes_read > 0)
    {
        i = 0;
        while (i < bytes_read)
        {
            if (buffer[i] == '\n')
            {
                char *temp = line;
                line = ft_strjoin(line, buffer, i+1);
                free(temp);
                char *temp_buffer = buffer;
                buffer = ft_substr(buffer, i + 1, bytes_read - i - 1);
                free(temp_buffer);
                return (line);
            }
            i++;
        }
        char *temp = line;
        line = ft_strjoin(line, buffer, bytes_read);
        free(temp);
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