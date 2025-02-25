/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:59:06 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 10:36:51 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void free_config(t_config *config)
{
    if (!config)
        return;
    if (config->textures)
    {
        free(config->textures->no_texture);
        free(config->textures->so_texture);
        free(config->textures->we_texture);
        free(config->textures->ea_texture);
        free(config->textures);
    }

    free(config->colors);
    free(config->map);
    free(config);
    exit(EXIT_FAILURE);
}
