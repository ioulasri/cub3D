/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:41:34 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 14:15:57 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	is_texture_line(const char *line)
{
	char	**split;
	int		ret;

	ret = 0;
	if (!line)
		return (0);
	split = ft_split(line, ' ');
	if (split && split[0])
	{
		if (ft_strcmp(split[0], "NO") == 0
			|| ft_strcmp(split[0], "SO") == 0
			|| ft_strcmp(split[0], "WE") == 0
			|| ft_strcmp(split[0], "EA") == 0)
			ret = 1;
	}
	free_array(split);
	return (ret);
}

int	is_color_line(const char *line)
{
	char	**split;
	int		ret;

	ret = 0;
	if (!line)
		return (0);
	split = ft_split(line, ' ');
	if (split && split[0])
	{
		if (ft_strcmp(split[0], "F") == 0
			|| ft_strcmp(split[0], "C") == 0)
			ret = 1;
	}
	free_array(split);
	return (ret);
}

int	is_map_line(const char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	if (!line || !line[0])
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != '\n')
			return (0);
		if (line[i] != ' ' && line[i] != '\n')
			found = 1;
		i++;
	}
	return (found);
}


int	check_textures_dup(t_map_file *file)
{
	int		i;
	int		counts[4];
	char	**split;

	i = 0;
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	while (file->arr[i])
	{
		split = ft_split(file->arr[i], ' ');
		if (split && split[0])
		{
			if (ft_strcmp(split[0], "NO") == 0)
				counts[0]++;
			else if (ft_strcmp(split[0], "SO") == 0)
				counts[1]++;
			else if (ft_strcmp(split[0], "WE") == 0)
				counts[2]++;
			else if (ft_strcmp(split[0], "EA") == 0)
				counts[3]++;
		}
		free_array(split);
		i++;
	}
	if (counts[0] > 1 || counts[1] > 1 ||
	    counts[2] > 1 || counts[3] > 1)
		return (1);
	return (0);
}

int	check_color_dup(t_map_file *file)
{
	int		i;
	int		counts[2];
	char	**split;

	i = 0;
	counts[0] = 0;
	counts[1] = 0;
	while (file->arr[i])
	{
		split = ft_split(file->arr[i], ' ');
		if (split && split[0])
		{
			if (ft_strcmp(split[0], "F") == 0)
				counts[0]++;
			else if (ft_strcmp(split[0], "C") == 0)
				counts[1]++;
		}
		free_array(split);
		i++;
	}
	if (counts[0] > 1 || counts[1] > 1)
		return (1);
	return (0);
}

int	check_duplicates(t_map_file *file)
{
	if (check_textures_dup(file))
    {
        print_error("Error: Duplicate textures.");
        return (1);
    }
		
	if (check_color_dup(file))
    {
        print_error("Error: Duplicate colors.");
        return (1);
    }
	return (0);
}

int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int is_invalid_line(const char *line)
{
    if (!line)
        return (1);
    if (is_texture_line(line))
        return (0);
    if (is_color_line(line))
        return (0);
    if (is_map_line(line))
        return (0);
    if (is_empty_line(line))
        return (0);
    return (1);
}


int	invalid_line(t_map_file *file, int *index)
{
	int	i;

	i = 0;
	while (file->arr[i])
	{
		if (is_invalid_line(file->arr[i]))
        {
            *index = i;
            return (1);
        }
		i++;
	}
	return (0);
}

void    print_combined_error(char *str1, int number)
{
    write(STDERR_FILENO, str1, ft_strlen(str1));
    ft_putnbr_fd(number, STDERR_FILENO);
    write(STDERR_FILENO, "\n", 1);
}

int	wrong_order(t_map_file *file)
{
	int		i;
	t_phase	phase;

	i = 0;
	phase = PHASE_TEXTURES;
	while (file->arr[i])
	{
		if (is_empty_line(file->arr[i]))
		{
			i++;
			continue ;
		}
		if (is_texture_line(file->arr[i]))
		{
			if (phase != PHASE_TEXTURES)
				return (1);
		}
		else if (is_color_line(file->arr[i]))
		{
			if (phase == PHASE_MAP)
				return (1);
			phase = PHASE_COLORS;
		}
		else if (is_map_line(file->arr[i]))
		{
			phase = PHASE_MAP;
		}
		else
			return (1);
		i++;
	}
	return (0);
}

void valid_map_file(t_map_file *file)
{
    int index;
    
    if (!file)
    {
        print_error("cannot open map file");
        exit(EXIT_FAILURE);
    }
    if (check_duplicates(file))
    {
        free_map_file(file);
        exit(EXIT_FAILURE);
    }
    if (invalid_line(file, &index))
    {
        free_map_file(file);
        print_combined_error("Error: Invalid line at: ", index);
        exit(EXIT_FAILURE);
    }
    if (wrong_order(file))
    {
        print_error("Error: wrong order");
        free_map_file(file);
        exit(EXIT_FAILURE);
    }
}