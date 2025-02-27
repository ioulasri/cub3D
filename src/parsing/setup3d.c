/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:59:52 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/27 17:31:36 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	setup3d(t_config *config)
{
	int	width = WIDTH;
	int	height = HEIGHT;
	int	bpp;
	int	line_length;
	int	endian;

	config->graphics->img_3d = mlx_new_image(config->graphics->mlx, width, height);
	if (!config->graphics->img_3d)
		print_error("Failed to create 3D image");
	config->graphics->img_3d_data = mlx_get_data_addr(config->graphics->img_3d,
		&bpp, &line_length, &endian);
	/* Save these values globally for later use */
	config->graphics->bpp = bpp;
	config->graphics->line_length = line_length;
	config->graphics->endian = endian;
}

/* Set a pixel in the 3D image using our dedicated data pointer */
void	my_bg_pixel_put_3d(t_config *config, int x, int y, int color)
{
	char	*dst;
	int		img_w;
	int		img_h;
	int		full_bpp = config->graphics->bpp / 8;

	/* Here we assume the 3D image covers the whole window */
	img_w = WIDTH;
	img_h = HEIGHT;
	if (x < 0 || x >= img_w || y < 0 || y >= img_h)
		return ;
	dst = config->graphics->img_3d_data + (y * config->graphics->line_length
			+ x * full_bpp);
	*(unsigned int *)dst = color;
}

/* Draw one cell in the 3D image – for now we use 50 as defined */
void	draw_cell_bg_3d(t_config *config, int col, int row, int color)
{
	int	i;
	int	j;
	int	start_x = col * 50;
	int	start_y = row * 50;

	i = 0;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			my_bg_pixel_put_3d(config, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

/* Draw the entire map into the 3D image using draw_cell_bg_3d */
void	draw_on_map(t_config *config)
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
			draw_cell_bg_3d(config, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_map_background_3d(t_config *config)
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
			draw_cell_bg_3d(config, j, i, color);
			j++;
		}
		i++;
	}
}

/* Render a simple gradient (placeholder for 3D view) into the 3D image */
void	render_3d(t_config *config)
{
	int x, y, r, g, b, color;
	int	width = WIDTH;
	int	height = HEIGHT;
	int	full_bpp = config->graphics->bpp / 8;
	int	pos;

	/* Create the 3D image */
	setup3d(config);
	draw_map_background_3d(config);
	mlx_put_image_to_window(config->graphics->mlx,
		config->graphics->win, config->graphics->img_3d, 0, 0);
}