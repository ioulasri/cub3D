/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:30:39 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 17:36:21 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	long long int	result;
	long long int	checker;
	int				sign;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		checker = result;
		result = result * 10 + sign * (str[i++] - 48);
		if (result > checker && sign < 0)
			return (0);
		if (result < checker && sign > 0)
			return (-1);
	}
	return (result);
}
