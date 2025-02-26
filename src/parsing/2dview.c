/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dview.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:32:57 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 18:29:33 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	redraw_scene(t_config *config)
{
	mlx_clear_window(config->graphics->mlx, config->graphics->win);
	mlx_put_image_to_window(config->graphics->mlx,
		config->graphics->win, config->graphics->bg_img, 0, 0);
	draw_enemies_radar(config);
	draw_player(config);
	draw_enemies(config);
}

int	collision(t_config *config, double x, double y)
{
	double	coll_r = 4.0;
	int		cell_start_x;
	int		cell_start_y;
	int		cell_end_x;
	int		cell_end_y;
	int		i;
	int		j;
	double	rx;
	double	ry;
	double	closestX;
	double	closestY;
	double	dx;
	double	dy;

	cell_start_x = (int)((x - coll_r) / CELL_SIZE);
	cell_start_y = (int)((y - coll_r) / CELL_SIZE);
	cell_end_x = (int)((x + coll_r) / CELL_SIZE);
	cell_end_y = (int)((y + coll_r) / CELL_SIZE);
	i = cell_start_y;
	while (i <= cell_end_y)
	{
		j = cell_start_x;
		while (j <= cell_end_x)
		{
			if (i >= 0 && i < config->map->height && j >= 0 && j < config->map->width)
			{
				if (config->map->grid[i][j] == '1')
				{
					rx = j * CELL_SIZE;
					ry = i * CELL_SIZE;
					closestX = (x < rx) ? rx : ((x > rx + CELL_SIZE) ? rx + CELL_SIZE : x);
					closestY = (y < ry) ? ry : ((y > ry + CELL_SIZE) ? ry + CELL_SIZE : y);
					dx = x - closestX;
					dy = y - closestY;
					if ((dx * dx + dy * dy) < (coll_r * coll_r))
						return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

void draw_hud(t_config *config)
{
	char	hud[128];
	char	num_buf[32];
	char	prefix[] = "Days remaining: ";
	int		n = (int)config->game->player->days;
	int		i = 31;
	int		neg = 0;

	num_buf[i] = '\0';
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	if (n == 0)
		num_buf[--i] = '0';
	while (n > 0 && i > 0)
	{
		num_buf[--i] = (n % 10) + '0';
		n /= 10;
	}
	if (neg && i > 0)
		num_buf[--i] = '-';
	ft_strlcpy(hud, prefix, sizeof(hud));
	ft_strlcat(hud, num_buf + i, sizeof(hud));
	mlx_string_put(config->graphics->mlx, config->graphics->win,
		10, 10, 0xFF0000, hud);
}


void	draw_death_message(t_config *config)
{
	int	win_width;
	int	win_height;
	int	text_width;
	int	text_height;

	win_width = config->map->width * CELL_SIZE;
	text_width = 250;
	text_height = 20;
	win_height = config->map->height * CELL_SIZE;
	mlx_clear_window(config->graphics->mlx, config->graphics->win);
	mlx_string_put(config->graphics->mlx, config->graphics->win,
		(win_width - text_width) / 2,
		(win_height - text_height) / 2,
		0xFF0000, "YOU HAVE BEEN ABSORBED BY THE BLACKHOLE");
}


int	update_player(void *param)
{
	t_config	*config;
	double		speed;
	double		old_x;
	double		old_y;
	double		new_x;
	double		new_y;

	config = (t_config *)param;
	update_enemies(config);
	draw_enemies_radar(config);
	speed = 0.01;
	old_x = config->game->player->x;
	old_y = config->game->player->y;
	new_x = old_x;
	new_y = old_y;
	if (config->game->keys.up)
		new_y -= speed;
	if (config->game->keys.down)
		new_y += speed;
	if (config->game->keys.left)
		new_x -= speed;
	if (config->game->keys.right)
		new_x += speed;
	if (new_x != old_x && new_y != old_y)
	{
		if (!collision(config, new_x, new_y))
		{
			config->game->player->x = new_x;
			config->game->player->y = new_y;
		}
		else
		{
			if (!collision(config, new_x, old_y))
				config->game->player->x = new_x;
			if (!collision(config, old_x, new_y))
				config->game->player->y = new_y;
		}
	}
	else
	{
		if (!collision(config, new_x, new_y))
		{
			config->game->player->x = new_x;
			config->game->player->y = new_y;
		}
	}
	if (config->game->player->days <= 0)
	{
		draw_death_message(config);
		return (0);  /* Freeze: do not update movement */
	}
	redraw_scene(config);
	draw_hud(config);
	return (0);
}


int	key_press(int keycode, t_config *config)
{
	if (keycode == ESCKEY)
		clean_and_exit(config);
	if (keycode == 'w' || keycode == 'W')
		config->game->keys.up = 1;
	else if (keycode == 's' || keycode == 'S')
		config->game->keys.down = 1;
	else if (keycode == 'a' || keycode == 'A')
		config->game->keys.left = 1;
	else if (keycode == 'd' || keycode == 'D')
		config->game->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_config *config)
{
	if (keycode == 'w' || keycode == 'W')
		config->game->keys.up = 0;
	else if (keycode == 's' || keycode == 'S')
		config->game->keys.down = 0;
	else if (keycode == 'a' || keycode == 'A')
		config->game->keys.left = 0;
	else if (keycode == 'd' || keycode == 'D')
		config->game->keys.right = 0;
	return (0);
}

void	minimap(t_config *config)
{
	config->graphics->mlx = mlx_init();
	if (!config->graphics->mlx)
		print_error("MLX init failed");
	config->graphics->win = mlx_new_window(config->graphics->mlx,
			WIDTH, HEIGHT, "2D Map");
	if (!config->graphics->win)
		print_error("MLX window creation failed");
	setup_image(config);
	draw_map_background(config);
	mlx_put_image_to_window(config->graphics->mlx,
		config->graphics->win, config->graphics->bg_img, 0, 0);
	mlx_hook(config->graphics->win, 2, 1L << 0, key_press, config);
	mlx_hook(config->graphics->win, 3, 1L << 1, key_release, config);
	mlx_loop_hook(config->graphics->mlx, update_player, config);
	mlx_loop(config->graphics->mlx);
}
