/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:01:11 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 20:01:26 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(t_map *map)
{
    if (!map)
        return;
    if (map->grid)
    {
        for (int i = 0; i < map->height; i++)
            free(map->grid[i]);
        free(map->grid);
    }
    free(map);
}
