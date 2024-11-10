/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:26:54 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/10 22:37:09 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"
#include <math.h>
#include <stdio.h>
void	set_coordinates(t_grid **vertex, int j, int i)
{
	int	offset;

	offset = 50 * i;
//	if (j == 0 && i == 0)
//	{
		//vertex[j][i].x = ((j - i) * cos(45)) + offset;
		//vertex[j][i].y = ((j + i) * sin(45) - vertex[j][i].z) + offset;
//	}
//	else
//	{	
//	vertex[j][i].x = ((j - i) * cos(45)) + offset + vertex[j][i - 1].x;
//	vertex[j][i].y = ((j + i) * sin(45) - vertex[j][i].z) + offset + vertex[j][i - 1].y;
//	}
	vertex[j][i].x = i + offset;
	vertex[j][i].y = j + offset;
}

	
			

		

int	atohex(char *element)
{
	int	i;

	i = 0;
	while (*element != ',')
		element++;
	element++;
	while (*element == '0' || *element == 'x')
		element++;
	while (*element != '\0')
	{
		if (*element >= 'a' && *element <= 'f') 
		{
			i = (i * 16) + *element  - 87;
			element++;
		}
		if (*element >= 'A' && *element <= 'F')
		{
			i = (i * 16) + *element - 55;
			element++;
		}
		if (*element >= '0' && *element <= '9')
		{
			i = (i * 16) + *element - '0';
			element++;
		}
	}
	return (i);
}

int	ft_chr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_grid	**set_widht(t_grid *point, char *argv)
{
	int	fd;
	int	i;
	int	j;
	t_grid  **vertex;
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
		vertex[j] = malloc(point->columns * sizeof(t_grid));
		if (!vertex[j])
			// free all previous allocatins
			return (NULL);
		while (elements[i])
		{		
			if (ft_chr(elements[i], ',') == 1)
			{
				vertex[j][i].row = atoi(elements[i]);
				temp = elements[i];
				vertex[j][i].color = atohex(temp);
				ft_printf("color = %d\n", vertex[j][i].color);
			}
			else
			{
				vertex[j][i].z = atoi(elements[i]);
				set_coordinates(vertex, j, i);
			}
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
void set_line(t_grid *point)
{
	float	dist_x;
	float	dist_y;
	float	steps;

	dist_x = point->xe - point->x;
	dist_y = point->ye - point->y;
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
	if (point->x > point->xe)
		point->increase_x *= -1;
	if (point->y > point->ye)
		point->increase_y *= -1;


	point->x = point->x + point->increase_x;
	point->y = point->y + point->increase_y;
}
/*
void	set_grid(char *argv)
{
	char	*get_line;
	char	**elements;
	t_grid	**coordinates;
	int	i;
	int	j;
	int	l;
	int	m;
	int	fd;
	coordinates = NULL;
	i = 0;
	j = 0;
	l = 0;
	m = 0;
	fd = open(argv, O_RDONLY);
	get_line = get_next_line(fd);
	ft_printf("%s\n", get_line);
	exit (1);
	
	while ((get_line = get_next_line(fd)) != NULL)
	{
		ft_printf("%s\n", get_line);
		elements = ft_split(get_line, ' ');
		while (elements[i])
		{
			coordinates[i][j].x = ft_atoi(elements[i]);
			i++;
	//		l++;
			ft_printf("coordinate%d\n", coordinates[i][j].x);
		}
	//	i++;
	//	j = 0;
	}
}
*/
void	set_grid(t_grid *point, char *argv)
{
	int	fd;
	char	*get_line;
	
	point->row = 0;
	fd = open(argv, O_RDONLY);
	while ((get_line = get_next_line(fd)) != NULL)
	{
		point->row++;
		point->columns = ft_count(get_line, ' ');
		free(get_line);
	}
	//ft_printf("rows%d\ncolumns%d\n", point->row, point->columns);
	close(fd);
}

void	drawing(t_data *data, int x, int y, int color)
{
	int	pixel;
	char	*image;
	pixel = (y * data->lenght) + x * (data->bit_pixel / 8);
	image = data->adrss + pixel;
	*(unsigned int*)image = color;
}

int main(int argc, char	**argv)
{
	int	i;
	int	j;
	void	*init;
	void	*window;
	t_data	img;
	t_grid	*point;
	//t_widht	grid;
	t_grid	**map;
	if (argc != 2)
		exit(1);
	point = malloc(sizeof(t_grid));
		if (!point)
			return (-1);	
	set_grid(point, argv[1]);
//	ft_printf("row%d columns%d\n", point->row, point->columns);
	map = set_widht(point, argv[1]);
	printf("*************%f\n", map[0][1].x);		
	i = 0;
	j = 0;
/*	while (i < point->row)
	{
		while (j < point->columns)
		{
			ft_printf("first_point %d = %d\n",j, map[i][j].x);
			j++;
		}
		j = 0;
		i++;
	}*/
//	point->x = 50;
//	point->y = 250;
//	point->xe = 920;
//	point->ye = 920;
	
	init = mlx_init();
	if (!init)
		return (MALLOC_ERROR);

	img.img = mlx_new_image(init, WIDHT, HEIGHT);
	img.adrss = mlx_get_data_addr(img.img, &img.bit_pixel, &img.lenght, &img.endian);
	window = mlx_new_window(init, WIDHT, HEIGHT, "The_fil");
	if (!window)
	{
		mlx_destroy_display(init);
		free(init);
		return (MALLOC_ERROR);
	}
//	set_grid(point, argv[1]);
			while(map[j][i].x != map[j][i + 1].x && map[j][i].y != map[j][i + 1].y)

			//while(j < point->row )
			{
			//	while (i < point->columns)
			//	{
			//		while (i < point->columns && map[j][i].x != map[j][i + 1].x)
			//		{
				drawing(&img, (int)map[j][i].x + 0.5, (int)map[j][i].y + 0.5, 0xFFFF00);
		//		drawing(&img, (int)point->x + 0.5, (int)point->y + 0.5, 0xFFFF00);
				set_line(&map[j][i]);
				printf("AAAAAAAAAAAAA%f\n", map[j][i].x);
	//			set_line(point);
			}
//				}
	//			i++;
	//			j++;
	//		}
			
	mlx_put_image_to_window(init, window, img.img, 0, 0); 
	mlx_loop(init);
	mlx_destroy_window(init, window);
	mlx_destroy_display(init);

}
