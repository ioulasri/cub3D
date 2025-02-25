/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:02:22 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 12:44:42 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int wrong_filetype(const char *path)
{
    int len;

    if (!path)
        return (1);
    len = ft_strlen(path);
    if (len < 4)
        return 1;
    if (ft_strcmp(path + len - 4, ".cub") != 0)
        return 1;
    return 0;
}


int open_file(const char *path)
{
    int fd;
    
    if (wrong_filetype(path))
    {
        print_error("Error: wrong file type '*.cub'");
        exit(EXIT_FAILURE);
    }
    fd = open(path, O_RDONLY);
    if (fd == -1)
        print_error("Error: Failed to open map file");
    return fd;
}

char **allocate_map_array(int capacity)
{
    char    **arr;
    
    arr = malloc(sizeof(char *) * capacity);
    if (!arr)
        print_error("Error: Failed to allocate memory for map array");
    return arr;
}

char **resize_map_array(char **arr, int *capacity, int size)
{
    char    **new_arr;
    int     i;

    *capacity *= 2;
    new_arr = malloc(sizeof(char *) * (*capacity));
    if (!new_arr)
    {
        print_error("Error: Failed to allocate memory for resized map array");
        i = 0;
        while (i < size)
        {
            free(arr[i]);
            i++;
        }
        free(arr);
        return NULL;
    }
    i = 0;
    while (i < size)
    {
        new_arr[i] = arr[i];
        i++;
    }
    free(arr);
    return new_arr;
}

int read_lines(int fd, t_map_file *file)
{
    char *line;
    char **new_arr;

    while ((line = get_next_line(fd)))
    {
        if (file->size >= file->capacity)
        {
            new_arr = resize_map_array(file->arr, &file->capacity, file->size);
            if (!new_arr)
            {
                free(line);
                return -1;
            }
            file->arr = new_arr;
        }
        file->arr[file->size++] = line;
    }
    return 0;
}
