#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/ft_dprintf.h"
#include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

# define ESC_KEY 65307
#  define LEFT_ARROW_KEY 65361
#  define RIGHT_ARROW_KEY 65363
#  define UP_ARROW_KEY 65362
#  define DOWN_ARROW_KEY 65364

//img for creat
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}				t_data;

 typedef struct s_map {
	size_t width;
	size_t height;
	char	**map;
}				t_map;

typedef struct  s_perso
{
	int	height_perso;
	int width_perso;
	int x;
	int y;
	t_data img_perso;
}				t_perso;


typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_perso	perso;
	t_data fond;
	t_map	*map;
}				t_vars;



int open_window(t_vars vars);
int map_test(char **argv);
int map_tab(char **argv, size_t i);
int map_valid(t_vars vars, size_t len);
char	*ft_strdup_long(const char *s);
int	close_window(int keycode, t_vars *vars);
size_t	ft_strlen_so_long(const char *str);
int map_duplicate(t_vars vars, size_t len);
int map_two(char **map_dup,  size_t len, t_vars vars);


#endif