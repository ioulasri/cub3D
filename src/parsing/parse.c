/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:20 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 15:16:32 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void exit_with_error_cleanup(const char *message, t_config *config)
{
    printf("Exit with error leaving");
    if (config)
        free_config(config);
    write(STDERR_FILENO, message, ft_strlen(message));
    write(STDERR_FILENO, "\n", 1);
    exit(EXIT_FAILURE);
}

void    print_array(char **str)
{
    int i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
}

void print_map(const t_map *map)
{
    int i;

    if (!map || !map->grid)
    {
        printf("(No map data to print)\n");
        return;
    }

    printf("Map (height=%d, width=%d):\n", map->height, map->width);
    for (i = 0; i < map->height; i++)
    {
        printf("%s\n", map->grid[i]);
    }
}

void	find_player_in_map(t_map *map)
{
	int	x;
	int	y;
	int	found;

	found = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' ||
				map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				map->start_x = x;
				map->start_y = y;
				map->start_dir = map->grid[y][x];
				found++;
			}
			x++;
		}
		y++;
	}
	if (found != 1)
		print_error("Map must contain exactly one player start");
}

void	setup_player(t_config *config)
{
	find_player_in_map(config->map);
	config->game->player->x = config->map->start_x * CELL_SIZE + (CELL_SIZE / 2);
    config->game->player->y = config->map->start_y * CELL_SIZE + (CELL_SIZE / 2);
	config->game->player->health = PLAYER_HEALTH;
	config->game->player->days = PLAYER_HEALTH / HEALTH_DAYS_RATIO;
    printf("x = %lf - y = %lf", config->game->player->x, config->game->player->y);
	config->game->player->angle = 0.0;
	config->game->player = config->game->player;
}

void	init_keys(t_keys *keys)
{
	keys->up = 0;
	keys->down = 0;
	keys->left = 0;
	keys->right = 0;
}

void	init_graphics(t_graphics *graphics)
{
	graphics->img = NULL;
	graphics->bg_img = NULL;
	graphics->win = NULL;
	graphics->mlx = NULL;
}

void	init_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		game->enemies[i].x = 0.0;
		game->enemies[i].y = 0.0;
		game->enemies[i].angle = 0.0;
		game->enemies[i].health = 100;
		game->enemies[i].speed = ENEMY_CHASE_SPEED + ((double)i / 500.0);
		printf("speed = %lf", game->enemies[i].speed);
		game->enemies[i].state = 0;
		i++;
	}
}

t_game	*init_game(t_config *config)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_with_error("Failed to allocate game");
	init_keys(&game->keys);
	game->num_enemies = 3;
	game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
	if (!game->enemies)
		exit_with_error("Failed to allocate enemies");
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		exit_with_error_cleanup("Error: Failed to allocate player", config);
	init_enemies(game);
	return (game);
}


t_config	*init_config(void)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		exit_with_error("Could not allocate config");
	config->textures = malloc(sizeof(t_textures));
	if (!config->textures)
		exit_with_error("Could not allocate textures");
	config->colors = malloc(sizeof(t_colors));
	if (!config->colors)
		exit_with_error("Could not allocate colors");
	config->map = malloc(sizeof(t_map));
	if (!config->map)
		exit_with_error("Could not allocate map");
	config->map->grid = NULL;
	/* Do not allocate config->file here; you'll assign it later */
	config->file = NULL;
	config->graphics = malloc(sizeof(t_graphics));
	if (!config->graphics)
		exit_with_error("Could not allocate graphics");
	init_graphics(config->graphics);
	config->game = init_game(config);
	return (config);
}

void	free_enemies(t_game *game)
{
	if (game && game->enemies)
		free(game->enemies);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->player)
		free(game->player);
	free_enemies(game);
	free(game);
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	if (config->textures)
	{
		free(config->textures->no_texture);
		free(config->textures->so_texture);
		free(config->textures->we_texture);
		free(config->textures->ea_texture);
		free(config->textures);
	}
	if (config->colors)
		free(config->colors);
	if (config->file)
		free_map_file(config->file);
	if (config->map)
		free_map(config->map);
	if (config->game)
		free_game(config->game);
	if (config->graphics)
	{
		if (config->graphics->img)
			mlx_destroy_image(config->graphics->mlx, config->graphics->img);
		if (config->graphics->bg_img)
			mlx_destroy_image(config->graphics->mlx, config->graphics->bg_img);
		if (config->graphics->win)
			mlx_destroy_window(config->graphics->mlx, config->graphics->win);
		if (config->graphics->mlx)
		{
			mlx_destroy_display(config->graphics->mlx);
			mlx_loop_end(config->graphics->mlx);
			free(config->graphics->mlx);
		}
		free(config->graphics);
	}
	free(config);
}

/* Compute Euclidean distance between two pixel positions */
double distance_px(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

/* Spawn a random enemy on a free cell ('0') in the map */
t_enemy spawn_random_enemy(t_config *config, int i)
{
	t_enemy enemy;
	int cellX, cellY;
	int attempts = 0;
	const int max_attempts = 1000;
	int found = 0;

	while (!found && attempts < max_attempts)
	{
		cellX = rand() % config->map->width;
		cellY = rand() % config->map->height;
		if (config->map->grid[cellY][cellX] == '0')
			found = 1;
		attempts++;
	}
	if (!found)
	{
		/* fallback: center of map */
		cellX = config->map->width / 2;
		cellY = config->map->height / 2;
	}
	enemy.x = cellX * CELL_SIZE + CELL_SIZE / 2.0;
	enemy.y = cellY * CELL_SIZE + CELL_SIZE / 2.0;
	enemy.angle = 0.0;
	enemy.speed = ENEMY_CHASE_SPEED + ((double)i / 1000.0);
	enemy.health = 100;
	enemy.state = 0; /* idle */
	return (enemy);
}

static int	count_free_cells(t_map *map)
{
	int		i;
	size_t	j;
	int		count = 0;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < ft_strlen(map->grid[i]))
		{
			if (map->grid[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	setup_enemies_random(t_config *config)
{
	int free_count;
	int num;
	int i;

	free_count = count_free_cells(config->map);
	num = free_count / ENEMY_FACTOR;
	if (num < MIN_ENEMIES)
		num = MIN_ENEMIES;
	config->game->num_enemies = num;
	config->game->enemies = malloc(sizeof(t_enemy) * num);
	if (!config->game->enemies)
		exit_with_error("Failed to allocate enemy array");
	i = 0;
	while (i < num)
	{
		config->game->enemies[i] = spawn_random_enemy(config, i);
		i++;
	}
}


void update_days_health(t_player *player)
{
	player->days = STARTING_DAYS - floor((STARTING_HEALTH - player->health) / HEALTH_DAYS_RATIO);
}

void	draw_circle_outline(t_config *config, int cx, int cy, int radius, int color)
{
	int	x = radius;
	int	y = 0;
	int	err = 0;

	while (x >= y)
	{
		mlx_pixel_put(config->graphics->mlx, config->graphics->win, cx + x, cy + y, color);
		mlx_pixel_put(config->graphics->mlx, config->graphics->win, cx + y, cy + x, color);
		mlx_pixel_put(config->graphics->mlx, config->graphics->win, cx - y, cy + x, color);
		mlx_pixel_put(config->graphics->mlx, config->graphics->win, cx - x, cy + y, color);
		mlx_pixel_put(config->graphics->mlx, config->graphics->win, cx - x, cy - y, color);
		mlx_pixel_put(config->graphics->mlx, config->graphics->win, cx - y, cy - x, color);
		mlx_pixel_put(config->graphics->mlx, config->graphics->win, cx + y, cy - x, color);
		mlx_pixel_put(config->graphics->mlx, config->graphics->win, cx + x, cy - y, color);
		y++;
		if (err <= 0)
			err += 2 * y + 1;
		if (err > 0)
		{
			x--;
			err -= 2 * x + 1;
		}
	}
}

void	draw_enemies_radar(t_config *config)
{
	int	i;
	int	radius = DAMAGE_THRESHOLD;  /* Radar circle radius */
	int	radar_color = RADAR_COLOR;    /* For example, #AAAAAA */

	i = 0;
	while (i < config->game->num_enemies)
	{
		t_enemy *enemy = &config->game->enemies[i];
		draw_circle_outline(config, (int)enemy->x, (int)enemy->y, radius, radar_color);
		i++;
	}
}

void update_enemies(t_config *config)
{
    int     i;
    double  d, dx, dy, norm;
    double  new_x, new_y;

    for (i = 0; i < config->game->num_enemies; i++)
    {
        t_enemy *enemy = &config->game->enemies[i];
        d = distance_px(enemy->x, enemy->y,
            config->game->player->x, config->game->player->y);
        if (d < FOLLOW_THRESHOLD)
        {
            dx = config->game->player->x - enemy->x;
            dy = config->game->player->y - enemy->y;
            norm = sqrt(dx * dx + dy * dy);
            if (norm > 0)
            {
                new_x = enemy->x + (dx / norm) * enemy->speed;
                new_y = enemy->y + (dy / norm) * enemy->speed;
                /* Check each axis separately to allow sliding */
                if (!collision(config, new_x, enemy->y))
                    enemy->x = new_x;
                if (!collision(config, enemy->x, new_y))
                    enemy->y = new_y;
                enemy->state = 1; /* chasing */
            }
        }
        else
            enemy->state = 0; /* idle */
        if (d < DAMAGE_THRESHOLD)
        {
            config->game->player->health -= ENEMY_DAMAGE;
            if (config->game->player->health < 0)
                config->game->player->health = 0;
            update_days_health(config->game->player);
        }
    }
}

t_config	*game_config(t_map_file *map_file)
{
	t_config	*config;

	config = init_config();
	if (!get_textures(map_file, config->textures) || !config->textures)
		exit_with_error_cleanup("Error: Textures parsing failed", config);
	print_textures(config->textures);
	if (get_flce_colors(map_file, config->colors))
		exit_with_error_cleanup("Error: Colors parsing failed", config);
	print_colors(config->colors);
	if (get_map(map_file, config->map))
		exit_with_error_cleanup("Error: Map parsing failed", config);
	setup_player(config);
	setup_enemies_random(config);
	config->file = map_file;
	return (config);
}
