/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:31:38 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 15:44:23 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*sr;
	unsigned char	*ds;
	size_t			i;

	if (dst == src)
		return (dst);
	sr = (unsigned char *)src;
	ds = (unsigned char *)dst;
	i = 0;
	if (ds > sr)
		while (len-- > 0)
			ds[len] = sr[len];
	else
	{
		while (i < len)
		{
			ds[i] = sr[i];
			i++;
		}
	}
	return (dst);
}
