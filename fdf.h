/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 07:01:31 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/09 22:29:46 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx-linux/mlx.h"
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define MALLOC_ERROR	1
# define HEIGHT 1000
# define WIDHT 1300

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

typedef struct	s_grid
{
	float	x;
	float	y;
	float	xe;
	float	ye;
	float	increase_x;
	float	increase_y;	
	
	int	row;
	int	columns;
	int	z;	
	int	color;	
}	t_grid;

#endif
