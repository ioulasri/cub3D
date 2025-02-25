/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:06:13 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 15:53:38 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

size_t	ft_len(char *str);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_line_allocation(int fd, char *str);
char	*ft_next_line(char *str);
char	*ft_rem_line(char *line);
char	*get_next_line(int fd);
#endif