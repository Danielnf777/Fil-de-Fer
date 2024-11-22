/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:44:37 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/20 15:59:46 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	drawing (t_grid **map, t_data *img, t_grid *point)
{
	draw_rows(map, img, point);
	draw_columns(map, img, point);
}
void draw_rows( t_grid **map, t_data *img, t_grid *point)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < point->row)
	{
		while (i + 1 < point->columns)
		{
			while (i < point->columns && map[j][i].x <= map[j][i + 1].x)
			{
				if ((map[j][i].x >=0 && map[j][i].x <= 2000) && (map[j][i].y >= 0 && map[j][i].y <= 2000))
					paint_pixel(img, (int)map[j][i].x + 0.5, (int)map[j][i].y + 0.5, map[j][i].color);
				set_line(&map[j][i], map[j][i + 1].x, map[j][i + 1].y);
			}
			i++;
		}
		j++;
		i = 0;
	}
}

void	draw_columns(t_grid **map, t_data *img, t_grid *point)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	reset_x(point, map);
//	set_coordinates(map, j, i);
	while (i < point->columns)
	{
		while (j  + 1 < point->row)
		{
			while (j < point->row && map[j][i].y <= map[j + 1][i].y)
			{
				if (map[j][i].y > 0 && map[j][i].y < 2000)	
					paint_pixel(img, (int)map[j][i].x + 0.5, (int)map[j][i].y + 0.5, map[j][i].color);
				set_line(&map[j][i], map[j + 1][i].x, map[j + 1][i].y);
			}
			j++;
		}
		i++;
		j = 0;
	}
}

void	reset_x(t_grid *point, t_grid **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < point->row)
	{
		while (i < point->columns)
		{
			map[j][i].x = i;
			set_coordinates(map, j, i);
			i++;
		}
		i = 0;
		j++;
	}
}
