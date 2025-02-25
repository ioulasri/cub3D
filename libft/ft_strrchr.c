/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:32:31 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 15:44:23 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char const	*found;

	found = NULL;
	while (*s)
	{
		if (*s == (char)c)
			found = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return ((char *)found);
}
