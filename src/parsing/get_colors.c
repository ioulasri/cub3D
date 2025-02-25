/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:55:59 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 10:40:02 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void print_color_debug(int color)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

    printf("Color hex: 0x%06X | RGB(%d, %d, %d)\n", color, r, g, b);
}

void print_colors(t_colors *colors)
{
    printf("Floor:  ");
    print_color_debug(colors->floor_color);
    printf("Ceiling:");
    print_color_debug(colors->ceiling_color);
}

static int	parse_color_string(const char *str, int *out_color)
{
	char	**split;
	int		r, g, b;

	split = ft_split(str, ',');
    print_array(split);
	if (!split)
		return (-1);
	if (!split[0]|| !split[1] || !split[2] ||
    split[0][0] == '\n' || split[1][0] == '\n' || split[2][0] == '\n')
    {
        free_array(split);
        return (-1);
    }
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_array(split);
		return (-1);
	}
	*out_color = (r << 16) | (g << 8) | b;
	free_array(split);
	return (0);
}

int get_flce_colors(t_map_file *map_file, t_colors *colors)
{
    char *floor_str;
    char *ceil_str;

    floor_str = get_key_value(map_file->arr, "F");
    if (!floor_str)
        exit_with_error_cleanup("Missing F color", map_file, NULL);

    ceil_str = get_key_value(map_file->arr, "C");
    if (!ceil_str)
    {
        free(floor_str);
        exit_with_error_cleanup("Missing C color", map_file, NULL);
    }
    if (parse_color_string(floor_str, &colors->floor_color) == -1)
    {
        free(floor_str);
        free(ceil_str);
        exit_with_error_cleanup("Invalid F color format", map_file, NULL);
    }
    if (parse_color_string(ceil_str, &colors->ceiling_color) == -1)
    {
        free(floor_str);
        free(ceil_str);
        exit_with_error_cleanup("Invalid C color format", map_file, NULL);
    }
    free(floor_str);
    free(ceil_str);
}