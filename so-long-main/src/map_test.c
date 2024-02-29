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
	t_map *so_map;
	int fd;
	size_t y;
	
	y = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "so_long: %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	initialize_map(len);
	vars.map->map = malloc(sizeof(char *) * (len));
	if (!vars.map->map)
	{
		if (close(fd) == -1)
		{
			ft_dprintf(2, "so_long: %s: %s\n", argv[1], strerror(errno));
			exit(EXIT_FAILURE);
		}
		ft_dprintf(2, "so_long: %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		vars.map->map[y++] = ft_strdup_long(line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		ft_dprintf(2, "so_long: %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	free(line);
	map_valid(vars, len);
	map_duplicate(vars, len);
	open_window(vars);
	return (0);
}
t_map	*initialize_map(size_t len)
{
	t_map *new_map;

	new_map = malloc(sizeof(t_map));
	if(!new_map)
		return (NULL);
	new_map->map = malloc(sizeof(char *) * (len));
	if(!new_map->map)
		return(free(new_map), NULL);
	new_map->width = 0;
	new_map->height = 0;
	return (new_map);
}


int map_valid(t_vars vars, size_t len)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	vars.map->width = strlen(vars.map->map[0]);
	printf("%ldbitttteeee\n",vars.map->width);
	while (i < len-1)
	{
		
		while (vars.map->map[i][y])
		{	
			
			if ((i == 0 || i == len - 1) && y < vars.map->width - 2)
			{
				
				if(vars.map->map[i][y] != '1')
				{
					printf("haut ou bas mauvais");
					exit(EXIT_FAILURE);
				}
			}
			else if(vars.map->map[i][0] != '1' || vars.map->map[i][vars.map->width - 2] != '1')
			{
				printf("coter mauvais");
				exit(EXIT_FAILURE);	
			}
			y++;
		}
		y = 0;
		i++;
	}
	return (0);
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

