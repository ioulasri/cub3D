/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:58:38 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/25 10:36:02 by imoulasr         ###   ########.fr       */
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
    int start_x;
    int start_y;
    char start_dir; // 'N', 'S', 'E', 'W'
} t_map;

typedef struct s_config {
    t_textures *textures;
    t_colors    *colors;
    t_map *map;
} t_config;



int    get_textures(t_map_file *map_file, t_textures *textures);
void	get_map(t_map_file *file, t_map *map);
t_config	*game_config(t_map_file *map_file);
void		get_flce_colors(t_map_file *map_file, t_colors *colors);
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
int     valid_map_file(t_map_file *file);
void exit_with_error(const char *message);
