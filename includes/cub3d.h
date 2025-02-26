/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:24:34 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 19:48:32 by imoulasr         ###   ########.fr       */
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

# define CELL_SIZE 12
# define HEIGHT 1200
# define WIDTH 1000
# define ESCKEY 65307
# define FOLLOW_THRESHOLD 100
# define ENEMY_CHASE_SPEED 0.003
# define ENEMY_DAMAGE 1
# define DAMAGE_THRESHOLD 15
# define PLAYER_HEALTH 200000.0
# define STARTING_HEALTH 200000.0
# define HEALTH_DAYS_RATIO 2000
# define STARTING_DAYS STARTING_HEALTH / HEALTH_DAYS_RATIO
# define RADAR_COLOR 0xe40000
# define RADAR_ALPHA 0.3
# define RADAR_RADIUS DAMAGE_THRESHOLD
# define MIN_ENEMIES 3
# define ENEMY_FACTOR 50  /* one enemy per 20 free cells */
/* 1- parsing */

t_map_file *read_map(const char *path);
int open_file(const char *path);
char **allocate_map_array(int capacity);
char **resize_map_array(char **arr, int *capacity, int size);
int read_lines(int fd, t_map_file *file);
void	minimap(t_config *config);
void	draw_player(t_config *config);
void	draw_map_background(t_config *config);
void	draw_cell_bg(t_config *config, int col, int row, int color);
void	my_bg_pixel_put(t_config *config, int x, int y, int color);
void	setup_image(t_config *config);
void update_enemies(t_config *config);
void	draw_enemies(t_config *config);
int	collision(t_config *config, double x, double y);
void	draw_enemies_radar(t_config *config); 