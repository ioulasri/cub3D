/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:01:51 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 10:35:57 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void    free_array(char **array)
{
    int i;

    i = 0;
    if (!array && !array[0])
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void cleanup(t_config *config, t_map *map, t_colors *colors)
{
    free_map(map);
    free(colors);

    if (config)
    {

        if (config->textures)
        {
            free(config->textures->no_texture);
            free(config->textures->so_texture);
            free(config->textures->we_texture);
            free(config->textures->ea_texture);
            free(config->textures);
        }
        free(config);
    }
    exit(EXIT_FAILURE);
}

void exit_with_error(const char *message)
{
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, "\n", 1);
    exit(EXIT_FAILURE);
}