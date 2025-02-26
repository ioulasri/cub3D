/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:00:07 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 11:02:05 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void free_map_file(t_map_file *file)
{
    if (!file)
        return;
    if (file->arr)
    {
        for (int i = 0; i < file->size; i++)
        {
            free(file->arr[i]);
        }
        free(file->arr);
    }
    free(file);
    printf("HELLO\n\n\n");
}
