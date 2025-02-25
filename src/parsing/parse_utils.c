/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:10:41 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 09:34:27 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int contains_string(char **splitted_str, const char *key)
{
    int i;

    i = 0;
    if (!splitted_str || !key)
        return (0);
    while (splitted_str[i])
    {
        if (ft_strcmp(splitted_str[i], key) == 0 && i == 0)
            return (1);
        i++;
    }
    return (0);
}

char *fill_value(char **splitted_string)
{
    if (!splitted_string || !splitted_string[1])
        return (NULL);
    return (ft_strdup(splitted_string[1]));
}

char    *get_key_value(char **arr, const char *key)
{
    char    **split;
    int     i;
    char    *value;
    
    value = 0;
    i = 0;
    if (!arr || !key)
        return ((char *)0);
    while (arr[i])
    {
        split = ft_split(arr[i], ' ');
        if (contains_string(split, key))
            value = fill_value(split);
        free_array(split);
        if (value)
            break;
        i++;   
    }
    return (value);
}