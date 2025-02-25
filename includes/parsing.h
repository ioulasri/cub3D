/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:58:38 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 16:43:27 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define CELL_SIZE 20
# define ESCKEY 65307

typedef struct s_textures
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
}				t_textures;

typedef struct s_colors
{
	int	floor_color;
	int	ceiling_color;
}				t_colors;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	char	start_dir;
}				t_map;

typedef struct s_map_file
{
	char	**arr;
	int		size;
	int		capacity;
}				t_map_file;

typedef struct s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
}				t_keys;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}				t_player;

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		bpp;
	int		line_length;
	int		endian;
}				t_graphics;

typedef struct s_assets
{
	t_textures	*textures;
	t_colors	*colors;
}				t_assets;

typedef struct s_game
{
	t_map		*map;
	t_map_file	*file;
	t_keys		keys;
	t_player	*player;
}				t_game;

typedef struct s_config
{
	t_assets	*assets;
	t_game		*game;
	t_graphics	*graphics;
}				t_config;

typedef enum e_phase
{
    PHASE_TEXTURES,
    PHASE_COLORS,
    PHASE_MAP,
    PHASE_DONE
} t_phase;

int    get_textures(t_map_file *map_file, t_textures *textures);
int	get_map(t_map_file *file, t_map *map);
t_config	*game_config(t_map_file *map_file);
int get_flce_colors(t_map_file *map_file, t_colors *colors);
char    *get_key_value(char **arr, const char *key);
void 	print_textures(t_textures *textures);
void 	print_colors(t_colors *colors);
void    exit_with_error_cleanup(const char *message, t_map_file *file, t_config *config);
void    free_array(char **array);
void    print_array(char **array);
void    print_error(char *message);
void	free_map(t_map *map);
void 	cleanup(t_config *config, t_map *map, t_colors *colors);
void	free_config(t_config *config);
void	free_map_file(t_map_file *file);
void    remove_new_lines(t_textures *textures);
void 	remove_nl(char *str);
void     valid_map_file(t_map_file *file);
void     exit_with_error(const char *message);
void    create_game_map(t_map_file *file, t_config *config);
void	clean_and_exit(t_config *config, t_map_file *file);
void print_map(const t_map *map);
int	is_empty_line(const char *line);