/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:20 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 16:18:01 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void exit_with_error_cleanup(const char *message, t_map_file *file, t_config *config)
{
    printf("Exit with error leaving");
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

void	find_player_in_map(t_map *map)
{
	int	x;
	int	y;
	int	found;

	found = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' ||
				map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				map->start_x = x;
				map->start_y = y;
				map->start_dir = map->grid[y][x];
				found++;
			}
			x++;
		}
		y++;
	}
	if (found != 1)
		print_error("Map must contain exactly one player start");
}

void	setup_player(t_config *config)
{
	t_player	*player;

	find_player_in_map(config->map);
	player = malloc(sizeof(t_player));
	if (!player)
		exit_with_error_cleanup("Error: Failed to allocate player", config->file, config);
	player->x = config->map->start_x * CELL_SIZE + (CELL_SIZE / 2);
	player->y = config->map->start_y * CELL_SIZE + (CELL_SIZE / 2);
	player->angle = 0.0;
	config->player = player;
}



t_config    *game_config(t_map_file *map_file)
{
    t_config *config = malloc(sizeof(t_config));
    if (!config)
        exit_with_error("Error: Failed to allocate memory for config");
    init_config(config);
    if (!get_textures(map_file, config->textures) || !config->textures)
        exit_with_error_cleanup("", map_file, config);
    print_textures(config->textures);
    if (get_flce_colors(map_file, config->colors))
        exit_with_error_cleanup("", map_file, config);
    print_colors(config->colors);
    if (get_map(map_file, config->map))
        exit_with_error_cleanup("", map_file, config);
    setup_player(config);
    return config;
}