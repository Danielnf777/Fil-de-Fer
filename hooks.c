/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:40:40 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/21 17:29:07 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

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
