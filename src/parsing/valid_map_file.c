/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:41:34 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 10:11:00 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"



int valid_map_file(t_map_file *file)
{
    if (!file)
    {
        perror("cannot open map file");
        exit(EXIT_FAILURE);
    }
    // if (check_duplicates(file))
    // {
    //     free_map_file(file);
    //     exit(EXIT_FAILURE);
    // }
    // if (wrong_order(file))
    // {
    //     free_map_file(file);
    //     exit(EXIT_FAILURE);
    // }
    return (0);
}