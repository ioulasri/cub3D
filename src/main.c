/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:17:49 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 16:34:45 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
# include <stdio.h>

void    print_arr(char **arr)
{
    for (int i = 0; arr[i]; i++)
        printf("%s", arr[i]);
}


void	clean_and_exit(t_config *config, t_map_file *file)
{
    printf("Peace Leaving...");
	if (file)
		free_map_file(file);
    if (config)
		free_config(config);
	exit(EXIT_SUCCESS);
}

void	draw_cell(void *mlx, void *win, int col, int row, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = col * CELL_SIZE;
	start_y = row * CELL_SIZE;
	i = 0;
	while (i < CELL_SIZE)
	{
		j = 0;
		while (j < CELL_SIZE)
		{
			mlx_pixel_put(mlx, win, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

/*
** draw_map: Draws the entire map and overlays the player cell in red.
*/
void	draw_map(t_config *config)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < config->map->height)
	{
		j = 0;
		while (j < config->map->width)
		{
			if (j < (int)strlen(config->map->grid[i]))
			{
				if (config->map->grid[i][j] == '1')
					color = 0x000000;
				else
					color = 0xFFFFFF;
			}
			else
				color = 0xFFFFFF;
			draw_cell(config->mlx, config->win, j, i, color);
			j++;
		}
		i++;
	}
	/* Draw the player cell in red */
	draw_cell(config->mlx, config->win, config->map->start_x,
		config->map->start_y, 0xFF0000);
}

/*
** redraw_map: Clears the window and redraws the map.
*/
void	redraw_map(t_config *config)
{
	mlx_clear_window(config->mlx, config->win);
	draw_map(config);
}

/*
** can_move: Returns 1 if the cell at (x, y) is accessible (not a wall)
*/
int	can_move(t_map *map, int x, int y)
{
	int	len;

	if (y < 0 || y >= map->height)
		return (0);
	len = strlen(map->grid[y]);
	if (x < 0 || x >= len)
		return (0);
	if (map->grid[y][x] == '1')
		return (0);
	return (1);
}

/*
** key_hook: Handles key events for WASD movement and ESC to exit.
*/
int	key_hook(int keycode, t_config *config)
{
	int	new_x;
	int	new_y;

	new_x = config->map->start_x;
	new_y = config->map->start_y;
	if (keycode == 65307) // ESC key (Linux)
		exit(0);
	if (keycode == 'w' || keycode == 'W')
		new_y--;
	else if (keycode == 's' || keycode == 'S')
		new_y++;
	else if (keycode == 'a' || keycode == 'A')
		new_x--;
	else if (keycode == 'd' || keycode == 'D')
		new_x++;
	if (can_move(config->map, new_x, new_y))
	{
		config->map->start_x = new_x;
		config->map->start_y = new_y;
		redraw_map(config);
	}
	return (0);
}

/*
** start_2d_view: Initializes MLX, creates the window, draws the map, and starts the loop.
*/
void	start_2d_view(t_config *config)
{
	config->mlx = mlx_init();
	if (!config->mlx)
		print_error("MLX init failed");
	config->win = mlx_new_window(config->mlx,
			config->map->width * CELL_SIZE,
			config->map->height * CELL_SIZE, "2D Map");
	if (!config->win)
		print_error("MLX window creation failed");
	draw_map(config);
	mlx_key_hook(config->win, key_hook, config);
	mlx_loop(config->mlx);
}


int main(int ac, char **av)
{
    t_map_file *file;
    t_config *config;
    
    if (ac != 2)
    {
        print_error("Usage: ./cub3D <map_file.cub>");
        return 1;
    }
    file = read_map(av[1]);
    valid_map_file(file);
    print_arr(file->arr);
    config = game_config(file);
    create_game_map(file, config);
    start_2d_view(config);
    clean_and_exit(config, file);
    return 0;
}