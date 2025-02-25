/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_nl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:20:31 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/24 20:24:43 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void 	remove_nl(char *str)
{
    size_t len;
    
    if (!str)
        return;
    len = ft_strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void    remove_new_lines(t_textures *textures)
{
    remove_nl(textures->ea_texture);
    remove_nl(textures->we_texture);
    remove_nl(textures->no_texture);
    remove_nl(textures->so_texture);
}