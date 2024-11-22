/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 07:01:31 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/21 17:24:39 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx-linux/mlx.h"
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>

# define MALLOC_ERROR	1
# define HEIGHT 2000
# define WIDHT 2000

typedef struct s_buffer
{
	void	*init;
	void	*window;
}	t_buffer;

typedef struct s_data
{
	void	*img;
	char	*adrss;
	int		bit_pixel;
	int		lenght;
	int		endian;
}	t_data;

typedef struct s_widht
{
	int	row;
	int	columns;
}	t_widht;

typedef struct s_grid
{
	float	x;
	float	y;
	float	xe;
	float	ye;
	float	increase_x;
	float	increase_y;	
	int		row;
	int		columns;
	int		z;	
	int		color;	
}	t_grid;
void	set_coordinates(t_grid **vertex, int j, int i);
void	set_line(t_grid *point, float xe, float ye);
void	set_coordinates(t_grid **vertex, int j, int i);
void	set_grid(t_grid *point, char *argv);
void	drawing(t_grid **map, t_data *img, t_grid *point);
void	draw_columns(t_grid **map, t_data *img, t_grid *point);
void	draw_rows( t_grid **map, t_data *img, t_grid *point);
void	paint_pixel(t_data *data, int x, int y, int color);
void	reset_x(t_grid *point, t_grid **map);
void	hooks(t_buffer *start);
int		escape(int keysym, t_buffer *start);
int		close_window(t_buffer *start);
int		handle_input(int keysym, t_data *data);
int		counter(char const *s, char c);
int		atohex(char *element);
int		ft_chr(const char *s, int c);
t_grid	**set_widht(t_grid *point, char *argv);

#endif
