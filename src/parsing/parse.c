/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:20 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 10:39:53 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void exit_with_error_cleanup(const char *message, t_map_file *file, t_config *config)
{
    if (file)
        free_map_file(file);
    if (config)
        free_config(config);
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, "\n", 1);
    exit(EXIT_FAILURE);
}

void    print_array(char **str)
{
    int i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
}

void init_config(t_config *config)
{
    ft_bzero(config, sizeof(t_config));

    config->textures = ft_calloc(1, sizeof(t_textures));
    if (!config->textures)
        exit_with_error("Cannot allocate textures");

    config->colors = ft_calloc(1, sizeof(t_colors));
    if (!config->colors)
    {
        free(config->textures);
        exit_with_error("Cannot allocate colors");
    }

    config->map = ft_calloc(1, sizeof(t_map));
    if (!config->map)
    {
        free(config->textures);
        free(config->colors);
        exit_with_error("Cannot allocate map");
    }
}


void print_map(const t_map *map)
{
    int i;

    if (!map || !map->grid)
    {
        printf("(No map data to print)\n");
        return;
    }

    printf("Map (height=%d, width=%d):\n", map->height, map->width);
    for (i = 0; i < map->height; i++)
    {
        printf("%s\n", map->grid[i]);
    }
}

t_config    *game_config(t_map_file *map_file)
{
    t_config *config = malloc(sizeof(t_config));
    if (!config)
        exit_with_error("Error: Failed to allocate memory for config");
    init_config(config);
    if (!get_textures(map_file, config->textures) || !config->textures)
        free_config(config);
    print_textures(config->textures);
    if (!get_flce_colors(map_file, config->colors))
        free_config(config);
    print_colors(config->colors);
    get_map(map_file, config->map);
    print_map(config->map);
    return config;
}