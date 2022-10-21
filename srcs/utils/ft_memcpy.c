/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:35:29 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/21 11:35:31 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	char		*sorc;
	size_t		i;

	sorc = (char *)src;
	dest = (char *)dst;
	i = 0;
	if (dst != 0 || src != 0)
	{
		while (i < n)
		{
			dest[i] = sorc[i];
			i++;
		}
	}
	return (dst);
}
