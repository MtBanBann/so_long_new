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

int open_window(t_vars vars)
{
	char	*wall = "./wall.xpm";
	char	*perso = "./perso.xpm";
	char	*collectible = "./collectible.xpm";
	char	*fonds = "./fond.xpm";
	int		img_width;
	int		img_height;
	size_t i;
	int y;
	int height;
	int width;
	t_data	img;
	t_data	collect;

	i = 0;
	y = 0;
	height = 0;
	width = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "so long");
	img.img = mlx_xpm_file_to_image(vars.mlx, wall, &img_width, &img_height);
	collect.img = mlx_xpm_file_to_image(vars.mlx, collectible, &img_width, &img_height);
	vars.fond.img = mlx_xpm_file_to_image(vars.mlx, fonds, &img_width, &img_height);
	if (img.img == NULL)
	{
		printf("Error: Failed to load image\n");
		exit(1);
	}
	vars.perso.img_perso.img = mlx_xpm_file_to_image(vars.mlx, perso, &img_width, &img_height);
	if (vars.perso.img_perso.img == NULL)
	{
		printf("Error: Failed to load image\n");
		exit(1);
	}
	vars.perso.width_perso = 0; // Initialiser la position x du joueur
    vars.perso.height_perso = 0; // Initialiser la position y du joueur
	//img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	collect.addr = mlx_get_data_addr(collect.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	vars.fond.addr = mlx_get_data_addr(vars.fond.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	vars.perso.img_perso.addr = mlx_get_data_addr(vars.perso.img_perso.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while (y < 5)
	{
		while (i < vars.map->width - 1)
		{
			if (vars.map->map[y][i] == '1')
			{
				mlx_put_image_to_window(vars.mlx, vars.win, img.img, width, height);
			}
			if (vars.map->map[y][i] == '0')
			{
				mlx_put_image_to_window(vars.mlx, vars.win, vars.fond.img, width, height);
			}
			if (vars.map->map[y][i] == 'C')
			{
				mlx_put_image_to_window(vars.mlx, vars.win, collect.img, width, height);
			}
			if (vars.map->map[y][i] == 'P')
			{
				vars.perso.height_perso = height;
				vars.perso.width_perso = width;
				vars.perso.x = y;
				vars.perso.y = i;
			}
			width = width + 100;
			i++;			
		}
		width = 0;
		height = height + 100;
		i = 0;
		y++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.perso.img_perso.img, vars.perso.width_perso, vars.perso.height_perso);
	
	mlx_hook(vars.win, 2, 1L<<0, close_window, &vars);
	

	mlx_loop(vars.mlx);

    return 0;
}

int	close_window(int keycode, t_vars *vars)
{
	if(keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == LEFT_ARROW_KEY)
    {
		//int old_x = vars->perso.width_perso;
        //int old_y = vars->perso.height_perso;
        // Déplacer le joueur vers la gauche
		if (vars->map->map[vars->perso.x][vars->perso.y - 1] == '1')
			return (0);
		else
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, vars->perso.width_perso, vars->perso.height_perso);
			vars->perso.y = vars->perso.y - 1;
			vars->perso.width_perso -= 100;
		}
		// Raffraîchir la fenêtre après le déplacement
        //mlx_clear_window(vars->mlx, vars->win);
		//mlx_put_image_to_window(vars.mlx, vars.win, fond.img, width, height);
        mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
    }
	if (keycode == RIGHT_ARROW_KEY)
    {
		//int old_x = vars->perso.width_perso;
        //int old_y = vars->perso.height_perso;
        // Déplacer le joueur vers la gauche
		
        if (vars->map->map[vars->perso.x][vars->perso.y + 1] == '1')
			return (0);
		else
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, vars->perso.width_perso, vars->perso.height_perso);
			vars->perso.y = vars->perso.y + 1;
			vars->perso.width_perso += 100;
		}
        // Raffraîchir la fenêtre après le déplacement
        //mlx_clear_window(vars->mlx, vars->win);
		
        mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
    }
	if (keycode == UP_ARROW_KEY)
    {
		//int old_x = vars->perso.width_perso;
        //int old_y = vars->perso.height_perso;
        // Déplacer le joueur vers la gauche
        if (vars->map->map[vars->perso.x - 1][vars->perso.y] == '1')
			return (0);
		else
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, vars->perso.width_perso, vars->perso.height_perso);
			vars->perso.x = vars->perso.x - 1;
			vars->perso.height_perso -= 100;
		}
        // Raffraîchir la fenêtre après le déplacement
        //mlx_clear_window(vars->mlx, vars->win);
		
        mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
    }
	if (keycode == DOWN_ARROW_KEY)
    {
		//int old_x = vars->perso.width_perso;
        //int old_y = vars->perso.height_perso;
        // Déplacer le joueur vers la gauche
        if (vars->map->map[vars->perso.x + 1][vars->perso.y] == '1')
			return (0);
		else
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->fond.img, vars->perso.width_perso, vars->perso.height_perso);
			vars->perso.x = vars->perso.x + 1;
			vars->perso.height_perso += 100;
		}
        // Raffraîchir la fenêtre après le déplacement
        //mlx_clear_window(vars->mlx, vars->win);
		
        mlx_put_image_to_window(vars->mlx, vars->win, vars->perso.img_perso.img, vars->perso.width_perso, vars->perso.height_perso);
    }
	return (0);
}

