/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:58:38 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 12:20:12 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_map_file {
    char **arr;
    int size;
    int capacity;
} t_map_file;

typedef struct s_textures {
    char	*no_texture;
    char	*so_texture;
    char	*we_texture;
    char	*ea_texture;
} t_textures;

typedef struct s_colors {
    int ceiling_color;
    int floor_color;
} t_colors;

typedef struct s_map {
    char **grid;
    int width;
    int height;
    double start_x;
    double start_y;
    char start_dir; // 'N', 'S', 'E', 'W'
} t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	health;
	// 42 blackhole concept
	double	days;
}				t_player;

typedef struct s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
}				t_keys;

typedef struct s_enemy
{
    double x;
    double y;
    double angle;
    int    health;
	double speed;
    int    state;
} t_enemy;


typedef struct s_game
{
	t_keys		keys;
	t_player	*player;
	t_enemy		*enemies;
	int			num_enemies;
}				t_game;

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	void	*bg_img;
	char	*bg_img_data;
	int		bpp;
	int		line_length;
	int		endian;
}				t_graphics;


typedef struct s_config
{
	t_textures	*textures;
	t_colors	*colors;
	t_map		*map;
	t_map_file	*file;
    t_game      *game;
	t_graphics  *graphics;
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
void    exit_with_error_cleanup(const char *message, t_config *config);
void    free_array(char **array);
void    print_array(char **array);
void    print_error(char *message);
int	compute_max_width(char **arr, int start, int lines);
void	free_map(t_map *map);
void 	cleanup(t_config *config, t_map *map, t_colors *colors);
void	free_config(t_config *config);
void	free_map_file(t_map_file *file);
void    remove_new_lines(t_textures *textures);
void 	remove_nl(char *str);
int     valid_map_file(t_map_file *file);
void     exit_with_error(const char *message);
void    create_game_map(t_map_file *file, t_config *config);
void	clean_and_exit(t_config *config);
void print_map(const t_map *map);
int	is_empty_line(const char *line);
int	check_valid_map(t_map *map);
int	key_press(int keycode, t_config *config);
int	key_release(int keycode, t_config *config);
