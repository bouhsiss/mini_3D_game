/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:04:42 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:04:44 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char		*c1;
	unsigned char		*c2;
	size_t				i;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (c1[i] && c2[i] && i < n - 1 && c1[i] == c2[i])
		i++;
	return (c1[i] - c2[i]);
}
