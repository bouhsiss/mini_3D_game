/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:03:54 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/16 18:21:40 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || \
		c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

bool	ft_isspace_v2(char c)
{
	if (c == ' ' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}
