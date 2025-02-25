/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:17:49 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 10:29:46 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
# include <stdio.h>

void    print_arr(char **arr)
{
    for (int i = 0; arr[i]; i++)
        printf("%s", arr[i]);
}

int main(int ac, char **av)
{
    t_map_file *file;
    t_config *config;
    
    if (ac != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.cub>\n", av[0]);
        return 1;
    }
    file = read_map(av[1]);
    valid_map_file(file);
    print_arr(file->arr);
    config = game_config(file);
    cleanup(config, config->map, config->colors);
    free_map_file(file);
    return 0;
}