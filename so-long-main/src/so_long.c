/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:31:53 by afavier           #+#    #+#             */
/*   Updated: 2024/02/16 23:23:01 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/so_long.h"
#include "../minilibx-linux/mlx.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>


int main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	else
	{
		map_test(argv);

	}
	return (0);
}

t_vars *initialize_vars(t_map *map, int img_width, 	int	img_height)
{
	t_vars *new_vars;
	char	*perso = "./perso.xpm";
	char	*fonds = "./fond.xpm";
	char	*escape = "./escape.xpm";

	new_vars = malloc(sizeof(t_vars));
	if(!new_vars)
		return (NULL);
	new_vars->mlx = mlx_init();
	if (!new_vars->mlx)
	{
		free(new_vars);
		free_tab(map->map);
		free(map);
		exit(EXIT_FAILURE);
	}
	new_vars->win = mlx_new_window(new_vars->mlx, 1920, 1080, "so long");
	if (!new_vars->win)
	{
		mlx_destroy_display(new_vars->mlx);
		free(new_vars->mlx);
		free(new_vars);
		free_tab(map->map);
		free(map);
		exit(EXIT_FAILURE);
	}
	new_vars->map = map;
	new_vars->fond.img = mlx_xpm_file_to_image(new_vars->mlx, fonds, &img_width, &img_height);
	new_vars->escape.img = mlx_xpm_file_to_image(new_vars->mlx, escape, &img_width, &img_height);
	new_vars->perso.img_perso.img = mlx_xpm_file_to_image(new_vars->mlx, perso, &img_width, &img_height);
	if (new_vars->perso.img_perso.img == NULL)
	{
		printf("Error: Failed to load image\n");
		exit(1);
	}
	new_vars->fond.addr = mlx_get_data_addr(new_vars->fond.img, &new_vars->fond.bits_per_pixel, &new_vars->fond.line_length,
								&new_vars->fond.endian);
	new_vars->fond.addr = mlx_get_data_addr(new_vars->escape.img, &new_vars->escape.bits_per_pixel, &new_vars->escape.line_length,
								&new_vars->escape.endian);
	new_vars->perso.img_perso.addr = mlx_get_data_addr(new_vars->perso.img_perso.img, &new_vars->perso.img_perso.bits_per_pixel, &new_vars->perso.img_perso.line_length,
								&new_vars->perso.img_perso.endian);
	new_vars->perso.width_perso = 0; // Initialiser la position x du joueur
    new_vars->perso.height_perso = 0;
	new_vars->perso.x = 0; // Initialiser la position x du joueur
    new_vars->perso.y= 0;
	return (new_vars);
}

int open_window(t_map *map)
{
	char	*wall = "./wall.xpm";
	char	*collectible = "./collectible.xpm";

	int		img_width;
	int		img_height;
	size_t i;
	int y;
	int height;
	int width;
	t_data	img;
	t_data	collect;
	t_vars *vars;

	i = 0;
	y = 0;
	height = 0;
	width = 0;
	vars = initialize_vars(map, 100, 100);
	

	img.img = mlx_xpm_file_to_image(vars->mlx, wall, &img_width, &img_height);
	collect.img = mlx_xpm_file_to_image(vars->mlx, collectible, &img_width, &img_height);
	if (img.img == NULL)
	{
		printf("Error: Failed to load image\n");
		exit(1);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	collect.addr = mlx_get_data_addr(collect.img, &collect.bits_per_pixel, &collect.line_length,
								&collect.endian);

	while (y < 5)
	{
		while (i < vars->map->width - 1)
		{
			if (vars->map->map[y][i] == '1')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, img.img, width, height);
			}
			if (vars->map->map[y][i] == '0')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, width, height);
			}
			if (vars->map->map[y][i] == 'C')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, collect.img, width, height);
			}
			if (vars->map->map[y][i] == 'P')
			{
				vars->perso.height_perso = height;
				vars->perso.width_perso = width;
				vars->perso.x = y;
				vars->perso.y = i;
			}
			width = width + 100;
			i++;			
		}
		width = 0;
		height = height + 100;
		i = 0;
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
	
	mlx_hook(vars->win, 2, 1L<<0, close_window, vars);
	

	mlx_loop(vars->mlx);

    return 0;
}

int	close_window(int keycode, t_vars *vars)
{
	if(keycode == ESC_KEY)
	{
		free_vars_all(vars);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == LEFT_ARROW_KEY)
    {
		if (vars->map->map[vars->perso.x][vars->perso.y - 1] == '1')
			return (0);
		else
		{
			if (vars->map->map[vars->perso.x][vars->perso.y - 1] == 'C' && vars->map->collectible != 0)
				vars->map->collectible -= 1;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, vars->perso.width_perso, vars->perso.height_perso);
			vars->perso.y = vars->perso.y - 1;
			vars->perso.width_perso -= 100;
		}
        mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
    }
	if (keycode == RIGHT_ARROW_KEY)
    {
		
        if (vars->map->map[vars->perso.x][vars->perso.y + 1] == '1')
			return (0);
		else
		{
			if (vars->map->map[vars->perso.x][vars->perso.y + 1] == 'C' && vars->map->collectible != 0)
				vars->map->collectible -= 1;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, vars->perso.width_perso, vars->perso.height_perso);
			vars->perso.y = vars->perso.y + 1;
			vars->perso.width_perso += 100;
		}
		
        mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
    }
	if (keycode == UP_ARROW_KEY)
    {
        if (vars->map->map[vars->perso.x - 1][vars->perso.y] == '1')
			return (0);
		else
		{
			if (vars->map->map[vars->perso.x - 1][vars->perso.y] == 'C' && vars->map->collectible != 0)
				vars->map->collectible -= 1;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, vars->perso.width_perso, vars->perso.height_perso);
			vars->perso.x = vars->perso.x - 1;
			vars->perso.height_perso -= 100;
		}

		
        mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
    }
	if (keycode == DOWN_ARROW_KEY)
    {

        if (vars->map->map[vars->perso.x + 1][vars->perso.y] == '1')
			return (0);
		else
		{
			if (vars->map->map[vars->perso.x + 1][vars->perso.y] == 'C' && vars->map->collectible != 0)
				vars->map->collectible -= 1;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, vars->perso.width_perso, vars->perso.height_perso);
			vars->perso.x = vars->perso.x + 1;
			vars->perso.height_perso += 100;
		}

		
        mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
    }
	if (vars->map->collectible == 0)
	{
		printf("%d %d\n",vars->map->width_e, vars->map->height_e);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->escape.img, vars->map->width_e *100, vars->map->height_e *100);
		if (vars->perso.x == vars->map->height_e && vars->perso.y == vars->map->width_e)
		{
			free_vars_all(vars);
			mlx_destroy_window(vars->mlx, vars->win);
			exit(0);
		}
	}
	return (0);
}

void free_vars_all(t_vars *vars)
{
	printf("gg tu as fini le jeux");
	free_tab(vars->map->map);
	free(vars->map);
	free(vars->win);
	free(vars->mlx);
	free(vars);
	exit(0);
}