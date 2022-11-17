/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:03:54 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/17 00:39:55 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str && ft_isspace(str[i]))
		i++;
	return (i);
}

int	is_valid_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '0')
		return (1);
	return (0);
}

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\n')
		return (true);
	else
		return (false);
}
