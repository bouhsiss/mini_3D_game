/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closeWin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:44 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:01:47 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int closeWin(t_data *Data)
{
	mlx_destroy_window(Data->mlx_ptr, Data->win->mlx_win);
	freeArray((*Data).MapDisplay->map);
	exit(0);
}
