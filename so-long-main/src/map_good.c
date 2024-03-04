#include "../inc/so_long.h"
#include "../minilibx-linux/mlx.h"

int map_duplicate(t_map *so_map, size_t len)
{
	char **map_dup;
	size_t i;

	i = 0;
	map_dup = malloc(sizeof(char *) * (len + 1));
	if (!map_dup)
	{
		free_tab(so_map->map);
		free(so_map);
		exit(EXIT_FAILURE);
	}
	while (len > i)
	{
		map_dup[i] = ft_strdup(so_map->map[i]);
		if (!map_dup[i])
		{
			if (i > 0)
				free_tab(map_dup);
			free(map_dup);
			free_tab(so_map->map);
			free(so_map);
			exit(EXIT_FAILURE);
		}
		//printf("%s\n",map_dup[i]);
		i++;
	}
	map_dup[i] = NULL;
	map_two(map_dup, len, so_map);
	return (0);
}

int map_two(char **map_dup, size_t len, t_map *so_map)
{
	size_t i;
	size_t y;
	size_t p;
	int e;

	i = 1;
	y = 1;
	e = 0;
	p = 1;
	so_map->height = len;
	while (p == 1)
	{
		p = 0;
		while (so_map->height > i)
		{
			while (so_map->width > y)
			{
				if (map_dup[i][y] == 'e')
					e++;
				if (map_dup[i][y] == 'P' || map_dup[i][y] == '2')
				{
					if (map_dup[i+1][y] == '0' || map_dup[i+1][y] == 'C' || map_dup[i+1][y] == 'E')
					{
						map_dup[i+1][y] = '2';
						p = 1;
					}
					if (map_dup[i-1][y] == '0' || map_dup[i-1][y] == 'C' || map_dup[i-1][y] == 'E')
					{
						map_dup[i-1][y] = '2';
						p = 1;
					}
					if (map_dup[i][y-1] == '0' || map_dup[i][y-1] == 'C' || map_dup[i][y-1] == 'E')
					{	
						map_dup[i][y-1] = '2';
						p =1;
					}
					if (map_dup[i][y+1] == '0' || map_dup[i][y+1] == 'C' || map_dup[i][y+1] == 'E')
					{
						map_dup[i][y+1] = '2';
						p =1;
					}
				}
				y++;
			}
			y = 1;
			i++;
		}
		i = 1;
		y = 1;
	}
	i = 0;
	if (map_dup_valide(map_dup, so_map->height, so_map->width) == -1)
	{
		ft_dprintf(2, "so_long : Map invalid non finish");
		free_tab(map_dup);
		//free(map_dup);
		free_tab(so_map->map);
		free(so_map);
		exit(EXIT_FAILURE);
	}

	return (0);
}

int map_dup_valide(char **map_dup, int height, int width)
{
	int i;
	int y;

	i = 1;
	y = 1;
	while (height > i)
	{
		while (width > y)
		{
			if (map_dup[i][y] == 'C' || map_dup[i][y] == 'E')
			{
				return (-1);
			}
			y++;
		}
		y = 1;
		i++;
	}
	return (0);
}