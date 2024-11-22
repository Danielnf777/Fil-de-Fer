/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danavarr <danavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:52:21 by danavarr          #+#    #+#             */
/*   Updated: 2024/11/21 17:25:35 by danavarr         ###   ########.fr       */
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
			i = (i * 16) + *element - 87;
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
		if (*element == '\n')
			element++;
	}
	return (i);
}
