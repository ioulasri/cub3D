/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:56:53 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 09:38:57 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void    print_error(char *message)
{
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, "\n", 1);
}

void print_textures(t_textures *textures)
{
    if (!textures)
        return;
    printf("Textures:\n");
    printf("  North Texture: %s\n", textures->no_texture ? textures->no_texture : "Not set");
    printf("  South Texture: %s\n", textures->so_texture ? textures->so_texture : "Not set");
    printf("  West Texture: %s\n", textures->we_texture ? textures->we_texture : "Not set");
    printf("  East Texture: %s\n", textures->ea_texture ? textures->ea_texture : "Not set");
}

static bool texture_exists(const char *path)
{
    int fd = open(path, O_RDONLY);
    printf("path = %s\n", path);
    printf("fd = %d\n", fd);
    if (fd == -1)
        return false;
    close(fd);
    return true;
}

int check_textures_paths(t_textures *textures)
{
    remove_new_lines(textures);
    if (!textures->no_texture || !texture_exists(textures->no_texture))
    {
        print_error("Error: Cannot open NO texture");
        return (0);
    }   
    if (!textures->so_texture || !texture_exists(textures->so_texture))
    {
        print_error("Error: Cannot open SO texture");
        return (0);
    }   
    if (!textures->we_texture || !texture_exists(textures->we_texture))
    {
        print_error("Error: Cannot open WE texture");
        return (0);
    }   
    if (!textures->ea_texture || !texture_exists(textures->ea_texture))
    {
        print_error("Error: Cannot open EA texture");
        return (0);
    }   
    return (1);
}

void    init_textures(t_textures *textures)
{
    textures->ea_texture = NULL;
    textures->no_texture = NULL;
    textures->so_texture = NULL;
    textures->we_texture = NULL;
}

int    get_textures(t_map_file *map_file, t_textures *textures)
{
    init_textures(textures);
    textures->no_texture = get_key_value(map_file->arr, "NO");
    textures->so_texture = get_key_value(map_file->arr, "SO");
    textures->we_texture = get_key_value(map_file->arr, "WE");
    textures->ea_texture = get_key_value(map_file->arr, "EA");
    // if (!check_textures_paths(textures))
    //     return (0);
    return (1);
}

