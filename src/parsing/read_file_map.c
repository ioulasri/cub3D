/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:05:31 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 12:44:42 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void    empty_map(int fd, t_map_file *file)
{
    print_error("Error: Empty map");
    close(fd);
    free_map_file(file);
    exit(EXIT_FAILURE);
}

int fill_map(int fd, t_map_file *file)
{
    if (read_lines(fd, file) == -1)
    {
        close(fd);
        return -1;
    }
    if (file->size == 0)
    {
        empty_map(fd, file);
        return -1;
    }
    file->arr[file->size] = NULL;
    return 0;
}

t_map_file *read_map(const char *path)
{
    t_map_file  *file;
    int fd;
    
    fd = open_file(path);
    if (fd == -1)
        return NULL;
    file = malloc(sizeof(t_map_file));
    if (!file)
    {
        close(fd);
        return NULL;
    }
    file->size = 0;
    file->capacity = INITIAL_CAPACITY;
    file->arr = allocate_map_array(file->capacity);
    if (!file->arr)
    {
        close(fd);
        return NULL;
    }
    if (fill_map(fd, file) == -1)
    {
        free_map_file(file);
        return NULL;
    }
    close(fd);
    return file;
}
