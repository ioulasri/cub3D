/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:44:33 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 14:34:23 by imoulasr         ###   ########.fr       */
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

static void copy_map_lines(t_map_file *file, t_map *map, int map_start_idx, int map_lines)
{
    int i;

    map->grid = malloc(sizeof(char *) * (map_lines + 1));
    if (!map->grid)
        exit_with_error("Failed to malloc map->grid");

    i = 0;
    while (i < map_lines)
    {
        map->grid[i] = ft_strdup(file->arr[map_start_idx + i]);
        if (!map->grid[i])
        {
            for (int j = 0; j < i; j++)
                free(map->grid[j]);
            free(map->grid);
            exit_with_error("Failed to copy map line");
        }
        i++;
    }
    map->grid[i] = NULL;
    map->height = map_lines;
}

static void compute_map_width(t_map *map)
{
    int i;
    int len;
    int max_len = 0;

    for (i = 0; i < map->height; i++)
    {
        len = ft_strlen(map->grid[i]);
        if (len > max_len)
            max_len = len;
    }
    map->width = max_len;
}

int	get_map(t_map_file *file, t_map *map)
{
	int	i;
	int	map_lines;
	int	j;

	i = 0;
	while (file->arr[i] && !is_map_line(file->arr[i]))
		i++;
	if (!file->arr[i])
	{
		print_error("Missing Map");
		return (1);
	}
	printf("first line of the map: %s\n", file->arr[i]);
	map_lines = count_map_lines(file->arr, i);
	if (map_lines == 0)
	{
		print_error("Missing Map");
		return (1);
	}
	copy_map_lines(file, map, i, map_lines);
	compute_map_width(map);
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
