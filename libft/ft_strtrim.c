/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:32:34 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 15:44:23 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

static int	is_inset(char c, char const *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s2[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	set_variable(int *end, char const *s1, char const *s2)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	i--;
	while (i && is_inset(s1[i--], s2))
		;
	if (!i)
		*end = 1;
	else
		*end = i + 2;
}

char	*ft_strtrim(char const *s1, char const *s2)
{
	char	*res;
	int		end;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	while (*s1 && is_inset(*s1, s2))
		s1++;
	if (!*s1)
		return (ft_strdup(""));
	end = 1;
	set_variable(&end, s1, s2);
	res = malloc(sizeof(char) * (end + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < end)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
