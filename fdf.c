/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:26:54 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/21 17:50:28 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	paint_pixel(t_data *data, int x, int y, int color)
{
	int		pixel;
	char	*image;

	pixel = (y * data->lenght) + x * (data->bit_pixel / 8);
	image = data->adrss + pixel;
	*(unsigned int *)image = color;
}

int	main(int argc, char	**argv)
{
	t_buffer	start;
	t_data		img;
	t_grid		*point;
	t_grid		**map;

	if (argc != 2)
		exit(1);
	point = malloc(sizeof(t_grid));
	if (!point)
		return (-1);
	set_grid(point, argv[1]);
	map = set_widht(point, argv[1]);
	start.init = mlx_init();
	if (!start.init)
		return (MALLOC_ERROR);
	img.img = mlx_new_image(start.init, WIDHT, HEIGHT);
	img.adrss = mlx_get_data_addr(img.img, &img.bit_pixel,
			&img.lenght, &img.endian);
	start.window = mlx_new_window(start.init, WIDHT, HEIGHT, "The_fil");
	if (!start.window)
	{
		mlx_destroy_display(start.init);
		free(start.init);
		return (MALLOC_ERROR);
	}
	drawing(map, &img, point);
	mlx_put_image_to_window(start.init, start.window, img.img, 0, 0);
	mlx_key_hook(start.window, &escape, &start);
	mlx_hook(start.window, 17, 0, close_window, &start);
	mlx_loop(start.init);
	//mlx_destroy_display(start.init);
//	free(start.init);
}
