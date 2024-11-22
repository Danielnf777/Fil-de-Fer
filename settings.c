/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:50:14 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/22 19:56:27 by danavarr         ###   ########.fr       */
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

	offset = 20 * i;
	offset_y = 20 * j;
	frame = 0;
//	if (j == 0 && i == 0)
//	{
//		vertex[j][i].x += frame;
//		vertex[j][i].y += frame;
//	}
	vertex[j][i].x = i + offset + frame + 900;
	vertex[j][i].y = j + offset_y + frame - 300;
	new_x = vertex[j][i].x;
	new_y = vertex[j][i].y;
	vertex[j][i].x = ((new_x - new_y) * cos(M_PI / 6));
	vertex[j][i].y = ((new_x + new_y) * sin(M_PI / 6)) - vertex[j][i].z * 15;
//	vertex[j][i].y = (((new_x + new_y) - (vertex[j][i].z * 15)) * 
//		sin(M_PI / 6));
}

int	counter(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0' && *s)
	//	{
			count++;
	//		if (*s == '\n')
	//			count--;
	//	}
		while (*s != '\0' && *s != c)
			s++;
	}
	return (count);
}

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
	ft_printf("row = %d\n", point->row);
	ft_printf("columns = %d\n", point->columns);
	close(fd);
}

t_grid	**set_widht(t_grid *point, char *argv)
{
	int		fd;
	int		i;
	int		j;
	t_grid	**vertex;
	char	*get_line;
	char	**elements;
	char	*temp;

	vertex = malloc(point->row * sizeof(t_grid));
	if (!vertex)
		return (NULL);
	i = 0;
	j = 0;
	fd = open(argv, O_RDONLY);
	get_line = get_next_line(fd);
	while (get_line != NULL)
	{
		elements = ft_split(get_line, ' ');
		if (point->columns != counter(get_line, ' '))
		{
			while (elements[i])
			{
				free(elements[i]);
				i++;
			}
			free(get_line);
			exit (0);
		}
		vertex[j] = malloc(point->columns * sizeof(t_grid));
		if (!vertex[j])
			// free all previous allocatins
			return (NULL);
		while (elements[i])
		{
			vertex[j][i].color = 0x00CC00;
			if (ft_chr(elements[i], ',') == 1)
			{
				temp = elements[i];
				vertex[j][i].color = atohex(temp);
				ft_printf("color =  %d\n", vertex[j][i].color);
			}
			vertex[j][i].z = ft_atoi(elements[i]);
			set_coordinates(vertex, j, i);
			i++;
		}
		i = 0;
		j++;
		free(get_line);
		free(elements);
		get_line = get_next_line(fd);
	}
/*	i = 0;
	j = 0;
	while (i < point->row)
	{
		while (j < point->columns)
		{
			ft_printf("first_point %d = %d\n",j, coordinates[i][j].z);
			j++;
		}
		j = 0;
		i++;
	}*/
	close(fd);
	return (vertex);
}

void	set_line(t_grid *point, float xe, float ye)
{
	float	dist_x;
	float	dist_y;
	float	steps;

	dist_x = xe - point->x;
	dist_y = ye - point->y;
	if (dist_x < 0)
		dist_x = dist_x * (-1);
	if (dist_y < 0)
		dist_y = dist_y * (-1);
	if (dist_x > dist_y)
		steps = (dist_x);
	else
		steps = (dist_y);
	point->increase_x = (dist_x) / steps ;
	point->increase_y = (dist_y) / steps;
	if (point->x > xe)
		point->increase_x *= -1;
	if (point->y > ye)
		point->increase_y *= -1;
	point->x = point->x + point->increase_x;
	point->y = point->y + point->increase_y;
}
