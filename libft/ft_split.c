/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:31:56 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 15:44:23 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

static int	ft_count_words(const char *s, char del)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && s[i] == del)
			i++;
		if (s[i] && s[i] != del)
			counter++;
		while (s[i] && s[i] != del)
			i++;
	}
	return (counter);
}

static int	fill_array(char **result, char const **s, char c, int i)
{
	int	len;

	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	result[i] = malloc(sizeof(char) * (len + 1));
	if (!result[i])
	{
		while (i--)
			free(result[i]);
		free(result);
		return (1);
	}
	len = 0;
	while (**s && **s != c)
	{
		result[i][len] = **s;
		len++;
		(*s)++;
	}
	result[i][len] = '\0';
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		words_count;
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	words_count = ft_count_words(s, c);
	result = malloc(sizeof(char *) * (words_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s && *s == c)
		s++;
	while (i < words_count)
	{
		if (fill_array(result, &s, c, i))
			return (NULL);
		while (*s && *s == c)
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}
