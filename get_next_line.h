/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdalmas <evdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:12:19 by evdalmas          #+#    #+#             */
/*   Updated: 2025/01/08 13:59:58 by evdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>

char		*get_next_line(int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strlen(const char *str);
char		*ft_strchr(const char *s, int i);
char		*ft_strdup(const char *s);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif