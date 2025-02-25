/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:32:13 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 15:44:23 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	des_len;
	size_t	src_len;
	size_t	i;
	size_t	total;

	if ((!dest || !src) && !size)
		return (0);
	des_len = 0;
	while (dest[des_len] && des_len < size)
		des_len++;
	src_len = 0;
	while (src[src_len])
		src_len++;
	i = 0;
	if (des_len >= size)
		return (size + src_len);
	total = des_len + src_len;
	while (src[i] && des_len + 1 < size)
	{
		dest[des_len] = src[i];
		i++;
		des_len++;
	}
	dest[des_len] = '\0';
	return (total);
}
