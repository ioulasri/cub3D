/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dview_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:33:47 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 10:20:07 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	setup_image(t_config *config)
{
	int	width;
	int	height;
	int	bpp;
	int	line_length;
	int	endian;

	width = config->map->width * CELL_SIZE;
	height = config->map->height * CELL_SIZE;
	config->graphics->img = mlx_new_image(config->graphics->mlx, width, height);
	if (!config->graphics->img)
		print_error("MLX image creation failed");
	config->graphics->img_data = mlx_get_data_addr(config->graphics->img,
			&bpp, &line_length, &endian);
	config->graphics->bpp = bpp;
	config->graphics->line_length = line_length;
	config->graphics->endian = endian;
	config->graphics->bg_img = mlx_new_image(config->graphics->mlx, width, height);
	if (!config->graphics->bg_img)
		print_error("MLX background image creation failed");
	config->graphics->bg_img_data = mlx_get_data_addr(config->graphics->bg_img,
			&bpp, &line_length, &endian);
	/* We assume bg_img uses the same bpp, line_length, and endian */
}

void	my_bg_pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;
	int		img_w;
	int		img_h;

	img_w = config->map->width * CELL_SIZE;
	img_h = config->map->height * CELL_SIZE;
	if (x < 0 || x >= img_w || y < 0 || y >= img_h)
		return ;
	dst = config->graphics->bg_img_data + (y * config->graphics->line_length
			+ x * (config->graphics->bpp / 8));
	*(unsigned int *)dst = color;
}


void	draw_cell_bg(t_config *config, int col, int row, int color)
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
			my_bg_pixel_put(config, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map_background(t_config *config)
{
	int	i;
	int	j;
	int	color;
	char	*line;

	i = 0;
	while (i < config->map->height)
	{
		line = config->map->grid[i];
		j = 0;
		while (j < config->map->width)
		{
			if (j < (int)strlen(line))
			{
				if (line[j] == '1')
					color = 0x000000;
				else
					color = 0xFFFFFF;
			}
			else
				color = 0xFFFFFF;
			draw_cell_bg(config, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_config *config)
{
	int	size;
	int	px;
	int	py;
	int	x;
	int	y;

	size = 6;
	px = (int)config->game->player->x - size / 2;
	py = (int)config->game->player->y - size / 2;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_pixel_put(config->graphics->mlx, config->graphics->win,
				px + x, py + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	draw_enemies(t_config *config)
{
	int		i;
	int		size;
	int		px;
	int		py;
	int		x;
	int		y;
	t_enemy	*enemy;

	size = 6;
	i = 0;
	while (i < config->game->num_enemies)
	{
		enemy = &config->game->enemies[i];
		px = (int)enemy->x - size / 2;
		py = (int)enemy->y - size / 2;
		y = 0;
		while (y < size)
		{
			x = 0;
			while (x < size)
			{
				mlx_pixel_put(config->graphics->mlx, config->graphics->win,
					px + x, py + y, 0x00FF00);
				x++;
			}
			y++;
		}
		i++;
	}
}
