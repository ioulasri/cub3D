/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:24:34 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 16:08:43 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define MAP_LIMIT 2064
# define INITIAL_CAPACITY 100
# define CELL_SIZE 20
# define ESC_KEY 65307

/* 1- parsing */

t_map_file *read_map(const char *path);
int open_file(const char *path);
char **allocate_map_array(int capacity);
char **resize_map_array(char **arr, int *capacity, int size);
int read_lines(int fd, t_map_file *file);
