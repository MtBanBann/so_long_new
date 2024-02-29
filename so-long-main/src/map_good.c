#include "../inc/so_long.h"
#include "../minilibx-linux/mlx.h"

int map_duplicate(t_vars vars, size_t len)
{
	char **map_dup;
	size_t i;

	i = 0;
	map_dup = malloc(sizeof(char *) * (len));
	while (len > i)
	{
		map_dup[i] = ft_strdup(vars.map->map[i]);
		i++;
	}
	//printf("%d %d",players[0], players[1]);
	map_two(map_dup, len, vars);
	return (0);
}

int map_two(char **map_dup, size_t len, t_vars vars)
{
	size_t i;
	size_t y;
	size_t p;

	i = 1;
	y = 1;
	p = 1;
	vars.map->height = len -1;
	printf("%ld\n",vars.map->width);
	while (p == 1)
	{
		p = 0;
		while (vars.map->height > i)
		{
			while (vars.map->width > y)
			{
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
	while (vars.map->height >= i)
	{
		printf("%s",map_dup[i]);
		i++;
	}
	return (0);
}
