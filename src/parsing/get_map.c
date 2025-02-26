/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:44:33 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 10:59:30 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static bool is_map_line(const char *line)
{
	int  i = 0;
	bool found_map_char = false;

	// If it's an empty string, not a map line
	if (!line[0])
		return false;
	
	while (line[i])
	{
		// If there's any disallowed character, it's not a map line
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != '\n'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			return false;
		}
		// Record if we encounter at least one actual map character
		if (line[i] != ' ' && line[i] != '\n')
			found_map_char = true;
		i++;
	}

	// Require at least one non-space map char
	return found_map_char;
}


static int count_map_lines(char **arr, int start_index)
{
	int count = 0;

	while (arr[start_index])
	{
		if (!is_map_line(arr[start_index]))
			break;
		count++;
		start_index++;
	}
	return count;
}

char	*remove_spaces_tabs(char *s)
{
	int	i = 0;
	int	j = 0;
	
	if (!s)
		return (s);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
	return (s);
}

char	*copy_to_grid(const char *s, int width)
{
	int		i;
	int		len = ft_strlen(s);
	char	*res;

	res = malloc(width + 1);
	if (!res)
		return (NULL);
	for (i = 0; i < width; i++)
	{
		if (i == 0 || i == width - 1)
			res[i] = '1';
		else if (i < len)
			res[i] = (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') ? '0' : s[i];
		else
			res[i] = '0';
	}
	res[width] = '\0';
	printf("line = %s\n", res);
	return (res);
}

static void copy_map_lines(t_map_file *file, t_map *map, int map_start_idx, int map_lines)
{
	int i;

	map->grid = malloc(sizeof(char *) * (map_lines + 1));
	if (!map->grid)
		exit_with_error("Failed to malloc map->grid");

	i = 0;
	printf("start\n");
	while (i < map_lines)
	{
		map->grid[i] = copy_to_grid(file->arr[map_start_idx + i], map->width);
		//map->grid[i] = ft_strdup(file->arr[map_start_idx + i]);
		if (!map->grid[i])
		{
			for (int j = 0; j < i; j++)
				free(map->grid[j]);
			free(map->grid);
			exit_with_error("Failed to copy map line");
		}
		i++;
	}
	printf("end\n");
	map->grid[i] = NULL;
	print_array(map->grid);
	map->height = map_lines;
}

int	compute_max_width(char **arr, int start, int lines)
{
	int	i;
	int	max;
	int	len;

	max = 0;
	i = start;
	while (i < start + lines)
	{
		len = ft_strlen(remove_spaces_tabs(arr[i]));
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_map(t_map_file *file, t_map *map)
{
	int	i;
	int	map_lines;
	int	j;

	i = 0;
	if (valid_map_file(file))
		return (1);
	while (file->arr[i] && !is_map_line(file->arr[i]))
		i++;
	if (!file->arr[i])
	{
		print_error("Missing Map");
		return (1);
	}
	map_lines = count_map_lines(file->arr, i);
	if (map_lines == 0)
	{
		print_error("Missing Map");
		return (1);
	}
	map->width = compute_max_width(file->arr, i, map_lines);
	copy_map_lines(file, map, i, map_lines);
	j = i + map_lines;
	while (file->arr[j])
	{
		if (!is_empty_line(file->arr[j]))
		{
			print_error("Extra content after map");
			return (1);
		}
		j++;
	}
	return (0);
}

