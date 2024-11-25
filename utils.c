/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:52:21 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/25 02:50:58 by danavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

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
int             atohex(char *element)
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
			i = (i * 16) + *element - 87;
		if (*element >= 'A' && *element <= 'F')
			i = (i * 16) + *element - 55;
		if (*element >= '0' && *element <= '9')
		{
			i = (i * 16) + *element - '0';
		}
		element++;
	}
	return (i);
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
			count++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (count);
}

int	free_malloc(t_buffer	*start)
{
	mlx_destroy_display(start->init);
	free(start->init);
	return (MALLOC_ERROR);
}

void	error_map(t_grid *point, char *get_line, char **elements)
{
	int	i;

	i = 0;
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
}
