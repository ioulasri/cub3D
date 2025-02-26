/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:55:21 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 01:40:45 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	replace_spaces(t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < map->height)
	{
		len = strlen(map->grid[i]);
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == ' ')
			{
				if (i == 0 || i == map->height - 1 || j == 0 || j == len - 1)
					map->grid[i][j] = '1';
				else
					map->grid[i][j] = '0';
			}
			if (map->grid[i][j] == '\n')
				map->grid[i][j] = '\0';
			j++;
		}
		i++;
	}
}


int	check_borders(t_map *map)
{
	int	i;
	int	j;
	int	len;

	/* Check top border */
	j = 0;
	while (map->grid[0][j])
	{
		if (map->grid[0][j] != '1')
			return (0);
		j++;
	}
	/* Check bottom border */
	j = 0;
	while (map->grid[map->height - 1][j])
	{
		if (map->grid[map->height - 1][j] != '1')
			return (0);
		j++;
	}
	/* Check side borders */
	i = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (map->grid[i][0] != '1' || map->grid[i][len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	print_map_attributes(const t_map *map)
{
	if (!map)
	{
		printf("Map is NULL\n");
		return ;
	}
	printf("Map attributes:\n");
	printf("  Height: %d\n", map->height);
	printf("  Width: %d\n", map->width);
	printf("  Start X: %lf\n", map->start_x);
	printf("  Start Y: %lf\n", map->start_y);
	printf("  Start Direction: %c\n", map->start_dir);
}

int	update_x_y_start(t_map *map)
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
    {
		print_error("Map must contain exactly one player start");
        return (1);
    }
    return (0);
}

int	check_valid_map(t_map *map)
{
	if (map->height < 3 || map->width < 3)
	{
		print_error("Error: Map is too small");
		return (0);
	}
	replace_spaces(map);
	if (!check_borders(map))
	{
		print_error("Error: Map borders are not closed");
		return (0);
	}
	return (1);
}
  
void    create_game_map(t_map_file *file, t_config *config)
{
    (void)file;
    if (update_x_y_start(config->map))
        exit_with_error_cleanup("", config);
    print_map_attributes(config->map);
    if (!check_valid_map(config->map))
        exit_with_error_cleanup("", config);
    print_map(config->map);
}