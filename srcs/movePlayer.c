/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movePlayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:19 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:01:21 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	keyrelease(int keycode, t_data **data)
{
	if (keycode == 53)
		close_win((*data));
	if (keycode == S_KEY)
		(*data)->player->walkDirection = 0;
	if (keycode == W_KEY)
		(*data)->player->walkDirection = 0;
	if (keycode == LEFT_ARROW)
		(*data)->player->turnDirection = 0;
	if (keycode == RIGHT_ARROW)
		(*data)->player->turnDirection = 0;
	if (keycode == D_KEY)
	{
		(*data)->player->walkDirection = 0;
		(*data)->player->sideAngle = 0;
	}
	if (keycode == A_KEY)
	{
		(*data)->player->walkDirection = 0;
		(*data)->player->sideAngle = 0;
	}
	return (0);
}

int	move_player(int keycode, t_data **data)
{
	if (keycode == 53)
		close_win((*data));
	if (keycode == S_KEY)
		(*data)->player->walkDirection = -1;
	if (keycode == W_KEY)
		(*data)->player->walkDirection = 1;
	if (keycode == LEFT_ARROW)
		(*data)->player->turnDirection = 1;
	if (keycode == RIGHT_ARROW)
		(*data)->player->turnDirection = -1;
	if (keycode == D_KEY)
	{
		(*data)->player->walkDirection = -1;
		(*data)->player->sideAngle = 90;
	}
	if (keycode == A_KEY)
	{
		(*data)->player->walkDirection = 1;
		(*data)->player->sideAngle = 90;
	}
	return (0);
}
