/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:50:14 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/25 04:14:14 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	set_coordinates(t_grid **vertex, int j, int i)
{
	float	offset;
	float	offset_y;
	float	frame;
	float	new_x;
	float	new_y;

	offset = 30 * i;
	offset_y = 30 * j;
	frame = 0;
	vertex[j][i].x = i + offset + frame + 900;
	vertex[j][i].y = j + offset_y + frame - 300;
	new_x = vertex[j][i].x;
	new_y = vertex[j][i].y;
	vertex[j][i].x = ((new_x - new_y) * cos(M_PI / 6));
	vertex[j][i].y = ((new_x + new_y) * sin(M_PI / 6)) - vertex[j][i].z * 15;
//	vertex[j][i].y = (((new_x + new_y) - (vertex[j][i].z * 15)) * 
//		sin(M_PI / 6));
}
/*
void	set_color(t_grid *point, float steps, float xe, float ye)
{
	float	red;
	float	green;
	float	blue;
	int	i;

	i = 0;
	while (i <= point->steps)
	{
		red = ((point->steps - i) / point->steps)
			* ((point->color >> 16) + (i / point->steps));
		green = ((point->steps - i) / point->steps)
			* ((point->color >> 8) + (i / point->steps));
		blue = ((point->steps - i) / point->steps)
			* ((point->color & 0xFF) + (i / point->steps));

		i++;
	}
*/

void	set_grid(t_grid *point, char *argv)
{
	int		fd;
	char	*get_line;

	point->row = 0;
	fd = open(argv, O_RDONLY);
	get_line = get_next_line(fd);
	while (get_line != NULL)
	{
		point->row++;
		point->columns = counter(get_line, ' ');
		free(get_line);
		get_line = get_next_line(fd);
	}
	close(fd);
}

t_grid	**store_coordinates(t_grid *point, char *argv)
{
	int		fd;
	int		j;
	t_grid	**vertex;
	char	*get_line;
	char	**elements;

	vertex = malloc(point->row * sizeof(t_grid));
	if (!vertex)
		return (NULL);
	j = 0;
	fd = open(argv, O_RDONLY);
	get_line = get_next_line(fd);
	while (get_line != NULL)
	{
		elements = ft_split(get_line, ' ');
		error_map(point, get_line, elements);
		fill_vertex(elements, vertex, j, point);
		free_elements(elements, get_line);
		j++;
		get_line = get_next_line(fd);
	}
	close(fd);
	return (vertex);
}

/*
t_grid	**store_coordinates(t_grid *point, char *argv)
{
//	int		fd;
	int		i;
	int		j;
	t_grid	**vertex;
	char	*get_line;
	char	**elements;

	vertex = malloc(point->row * sizeof(t_grid));
	if (!vertex)
		return (NULL);
	i = 0;
	j = 0;
	point->fd = open(argv, O_RDONLY);
	get_line = get_next_line(point->fd);
	while (get_line != NULL)
	{
		elements = ft_split(get_line, ' ');
		error_map(point, get_line, elements);
		vertex[j] = malloc(point->columns * sizeof(t_grid));
		if (!vertex[j])
			// free all previous allocatins
			return (NULL);
		while (elements[i])
		{
			//dates_xy(elements[i], j, i);
			vertex[j][i].color = 0x00CC00;
			if (ft_chr(elements[i], ',') == 1)
			{
				vertex[j][i].color = atohex(elements[i]);
				ft_printf("88color =  %d\n", vertex[j][i].color);
			}
			vertex[j][i].z = ft_atoi(elements[i]);
			set_coordinates(vertex, j, i);
			i++;
		}
		free(get_line);
		i = 0;
		free_elements(elements, get_line);
//		while (elements[i])
//		{
//			free(elements[i]);
//			i++;
//		}
		free(elements);
		i = 0;
		j++;
		get_line = get_next_line(point->fd);
	}
	close(point->fd);
	return (vertex);
//	return (dates_xy
}
*/
void	set_line(t_grid *point, float xe, float ye)
{
	float	dist_x;
	float	dist_y;

	dist_x = xe - point->x;
	dist_y = ye - point->y;
	if (dist_x < 0)
		dist_x = dist_x * (-1);
	if (dist_y < 0)
		dist_y = dist_y * (-1);
	if (dist_x > dist_y)
		point->steps = (dist_x);
	else
		point->steps = (dist_y);
	point->increase_x = (dist_x) / point->steps ;
	point->increase_y = (dist_y) / point->steps;
	if (point->x > xe)
		point->increase_x *= -1;
	if (point->y > ye)
		point->increase_y *= -1;
	point->x = point->x + point->increase_x;
	point->y = point->y + point->increase_y;
//	set_color(point, steps, xe, ye);
}
int	fill_vertex(char **elements, t_grid **vertex, int j, t_grid *point)
{
	int	i;
	
	i = 0;
	vertex[j] = malloc(point->columns * sizeof(t_grid));
	if (!vertex[j])
		// free all previous allocatins
		return (MALLOC_ERROR);
	while (elements[i])
		{
			//dates_xy(elements[i], j, i);
			vertex[j][i].color = 0x00CC00;
			if (ft_chr(elements[i], ',') == 1)
			{
				vertex[j][i].color = atohex(elements[i]);
				ft_printf("88color =  %d\n", vertex[j][i].color);
			}
			vertex[j][i].z = ft_atoi(elements[i]);
			set_coordinates(vertex, j, i);
			i++;
		}
	return (0);
}

void	free_elements(char **elements, char *get_line)
{
	int	i;

	free(get_line);
	i = 0;
	while (elements[i])
	{
		free(elements[i]);
		i++;
	}
	free(elements);
}

