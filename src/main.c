/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:17:49 by imoulasr          #+#    #+#             */
/*   Updated: 2025/02/26 18:39:36 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s", arr[i]);
		i++;
	}
}

void	clean_and_exit(t_config *config)
{
	printf("Peace Leaving...");
	if (config)
		free_config(config);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_map_file	*file;
	t_config	*config;
	
	if (ac != 2)
	{
		print_error("Usage: ./cub3D <map_file.cub>");
		return (1);
	}
	file = read_map(av[1]);
	print_arr(file->arr);
	config = game_config(file);
	create_game_map(file, config);
	render(config);
	clean_and_exit(config);
	return (0);
}
