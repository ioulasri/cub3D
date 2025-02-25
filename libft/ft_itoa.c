/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:31:02 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 15:44:23 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

static int	num_length(long n)
{
	long	num;
	int		count;

	num = n;
	count = 0;
	if (num < 0)
	{
		count++;
		num = -num;
	}
	if (!num)
		return (1);
	while (num)
	{
		count++;
		num /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*result;
	int		i;
	long	num;

	num = n;
	size = num_length(num);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	i = size - 1;
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (i >= 0 && result[i] != '-')
	{
		result[i--] = num % 10 + 48;
		num /= 10;
	}
	return (result);
}
