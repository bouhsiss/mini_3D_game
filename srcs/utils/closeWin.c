/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closeWin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:44 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/04 18:37:39 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_win(t_data *Data)
{
	mlx_destroy_window(Data->mlx_ptr, Data->win->mlx_win);
	free_array((*Data).mapdisplay->map);
	exit(0);
}
