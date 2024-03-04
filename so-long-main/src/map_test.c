/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:31:58 by afavier           #+#    #+#             */
/*   Updated: 2024/02/16 22:08:57 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include "../minilibx-linux/mlx.h"

int map_test(char **argv)
{
	char *line;
	int		fd;
	size_t i;
	size_t len;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "so_long: %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		ft_dprintf(2, "so_long: error for read map get_next_line");
		exit(EXIT_FAILURE);
	}
	while (line)
	{
		if (i == 0)
			len = ft_strlen_so_long(line);
		else if (len != ft_strlen_so_long(line))
		{
			close(fd);
			free(line);
			ft_dprintf(2, "so_long: %s: map invalide\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (close(fd) == -1)
	{
		ft_dprintf(2, "so_long: %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	//free(line);
	map_tab(argv, i);
	return (0);
}

int map_tab(char **argv, size_t len)
{
	char *line;
	int fd;
	t_map *so_map;
	size_t y;
	
	y = 0;
	so_map = initialize_map(len);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "so_long: %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n",line);
		so_map->map[y++] = ft_strdup_long(line);
		if(!so_map->map[y - 1])
		{
			free_tab(so_map->map);
			free(so_map);
			ft_dprintf(2, "so_long : Error filling map");
			close(fd);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	so_map->map[y] = NULL;
	if (close(fd) == -1)
	{
		free_tab(so_map->map);
		free(so_map);
		ft_dprintf(2, "so_long: %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("%ld\n", len);
	free(line);
	map_valid(so_map, len);
	map_duplicate(so_map, len);
	open_window(so_map);
	return (0);
}
t_map	*initialize_map(size_t len)
{
	t_map *new_map;

	new_map = malloc(sizeof(t_map));
	if(!new_map)
	{
		ft_dprintf(2, "so_long : Error malloc new_map");
		exit(EXIT_FAILURE);
	}
	new_map->map = malloc(sizeof(char *) * (len + 1)); 
	if(!new_map->map)
	{
		ft_dprintf(2, "so_long : Error malloc new_map");
		free(new_map);
		exit(EXIT_FAILURE);
	}
	new_map->width = 0;
	new_map->height = 0;
	new_map->collectible = 0;
	new_map->height_e = 0;
	new_map->width_e = 0;
	return (new_map);
}


int map_valid(t_map *so_map, size_t len)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	so_map->width = strlen(so_map->map[0]);
	while (i < len-1)
	{
		while (so_map->map[i][y])
		{	
			
			if ((i == 0 || i == len - 1) && y < so_map->width - 2)
			{
				
				if(so_map->map[i][y] != '1')
				{
					printf("haut ou bas mauvais");
					free_tab(so_map->map);
					free(so_map);
					exit(EXIT_FAILURE);
				}
			}
			else if(so_map->map[i][0] != '1' || so_map->map[i][so_map->width - 2] != '1')
			{
				printf("coter mauvais");
				free_tab(so_map->map);
				free(so_map);
				exit(EXIT_FAILURE);	
			}
			y++;
		}
		y = 0;
		i++;
	}
	map_valide_collectible(so_map, len, 0, 0);
	return (0);
}

void map_valide_collectible(t_map *so_map, size_t len, int nb_e, int nb_p)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	while (i < len-1)
	{
		while (so_map->map[i][y])
		{
			if (so_map->map[i][y] == 'C')
				so_map->collectible += 1;
			if (so_map->map[i][y] == 'E')
			{
				so_map->height_e = i;
				so_map->width_e= y;
				printf("%ld %ld",i,y);
				nb_e++;
			}
			if (so_map->map[i][y] == 'P')
				nb_p++;
			y++;
		}
		y = 0;
		i++;
	}
	if (so_map->collectible == 0 || nb_e != 1 || nb_p != 1)
		free_so_map(so_map);
}

void free_so_map(t_map *so_map)
{
	ft_dprintf(2, "Map invalide");
	free_tab(so_map->map);
	free(so_map);
	exit(EXIT_FAILURE);	
}

char	*ft_strdup_long(const char *s)
{
	size_t	i;
	size_t	y;
	char	*tab;

	i = ft_strlen(s);
	y = 0;
	tab = malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	while (s[y])
	{
		tab[y] = s[y];
		y++;
	}
	tab[y] = '\0';
	return (tab);
}

size_t	ft_strlen_so_long(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

