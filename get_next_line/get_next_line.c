/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:06:46 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 15:53:36 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char		*out;
	static char	*str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = ft_line_allocation(fd, str);
	if (!str)
		return (NULL);
	out = ft_next_line(str);
	str = ft_rem_line(str);
	return (out);
}
