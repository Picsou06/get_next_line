/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdalmas <evdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:29:04 by evdalmas          #+#    #+#             */
/*   Updated: 2024/12/21 18:17:41 by evdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static char*	buffer;// = NULL;
    char* reader;
    char*	line = NULL;
    int		i;  
    int		bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    // verifier si on a une nl dans le buffer
    if (buffer)
    {
        size_t j;
        size_t buff_size;

        j = 0;
        buff_size = ft_strlen(buffer);
        while (buffer[j] && j < buff_size)
        {
            if (buffer[j] == '\n')
            {
                line = ft_substr(buffer, 0, j + 1);
                char * prev_buff = buffer;
                buffer = ft_substr(buffer, j + 1, buff_size - j);
                if (prev_buff)
                    free(prev_buff);
                return (line);
            }
            j++;
        }
        if (buff_size > 0)
            line = ft_substr(buffer, 0, buff_size);
        free(buffer);
        buffer = NULL;
    }

    if (!line)
    {
        line = (char *)malloc(1);
        if (!line)
        {
            return (NULL);
        }
        line[0] = '\0';
    }


    reader = malloc(BUFFER_SIZE + 1);

    if (!reader)
        return (NULL);

    bytes_read = read(fd, reader, BUFFER_SIZE);
    if (bytes_read < 0)
    {
        free(reader);
        free(buffer);
        buffer = NULL;
        free(line);
        return (NULL);
    }
    reader[bytes_read] = '\0';
    while (bytes_read > 0)
    {
        i = 0;
        while (i < bytes_read)
        {
            if (reader[i] == '\n')
            {
                char *temp = line;
                line = ft_strjoin(line, reader, i+1);
                free(temp);
                if (buffer)
                    free(buffer);
                buffer = ft_substr(reader, i + 1, bytes_read - i);
                free(reader);
                return (line);
            }
            i++;
        }
        char *temp = line;
        line = ft_strjoin(line, reader, bytes_read);
        free(temp);
        bytes_read = read(fd, reader, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(reader);
            free(buffer);
            buffer = NULL;
            free(line);
            return (NULL);
        }
        reader[bytes_read] = '\0';
    }
    free(reader);
    if (line[0] == '\0')
    {
        free(line);
        return (NULL);
    }
    return (line);
}