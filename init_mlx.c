/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:57:54 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/25 00:06:02 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	initialize_mlx(t_grid *point, t_grid **map)
{
	t_buffer	start;
	t_data		img;

	start.init = mlx_init();
	if (!start.init)
		return (MALLOC_ERROR);
	img.img = mlx_new_image(start.init, WIDHT, HEIGHT);
	img.adrss = mlx_get_data_addr(img.img, &img.bit_pixel,
			&img.lenght, &img.endian);
	start.window = mlx_new_window(start.init, WIDHT, HEIGHT, "The_fil");
	if (!start.window)
		free_malloc(&start);
	drawing(map, &img, point);
	mlx_put_image_to_window(start.init, start.window, img.img, 0, 0);
	mlx_key_hook(start.window, &escape, &start);
	mlx_hook(start.window, 17, 0, close_window, &start);
	mlx_loop(start.init);
	return (0);
}

int	escape(int keysym, t_buffer *start)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(start->init, start->window);
	}
	return (0);
}

int	close_window(t_buffer *start)
{
	mlx_destroy_window(start->init, start->window);
	return (0);
}
