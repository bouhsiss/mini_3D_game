/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:04:13 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:04:16 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		sz;

	sz = ft_strlen(s1);
	s2 = (char *)malloc(sz * sizeof (char) + 1);
	if (!(s2))
		return (0);
	ft_memcpy(s2, s1, sz);
	s2[sz] = '\0';
	return (s2);
}
