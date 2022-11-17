/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:19 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/16 23:21:14 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	button_press(int button_code, int x, int y, t_data **data)
{
	(void)y;
	(void)x;
	if (button_code == 1)
		(*data)->player->turn_direction = -1;
	if (button_code == 2)
		(*data)->player->turn_direction = 1;
	return (0);
}

int	button_release(int button_code, int x, int y, t_data **data)
{
	(void)y;
	(void)x;
	if (button_code == 1)
		(*data)->player->turn_direction = 0;
	if (button_code == 2)
		(*data)->player->turn_direction = 0;
	return (1);
}

int	keyrelease(int keycode, t_data **data)
{
	if (keycode == 53)
		close_win((*data));
	if (keycode == S_KEY)
		(*data)->player->walk_direction = 0;
	if (keycode == W_KEY)
		(*data)->player->walk_direction = 0;
	if (keycode == LEFT_ARROW)
		(*data)->player->turn_direction = 0;
	if (keycode == RIGHT_ARROW)
		(*data)->player->turn_direction = 0;
	if (keycode == D_KEY)
	{
		(*data)->player->walk_direction = 0;
		(*data)->player->side_angle = 0;
	}
	if (keycode == A_KEY)
	{
		(*data)->player->walk_direction = 0;
		(*data)->player->side_angle = 0;
	}
	return (0);
}

int	key_press(int keycode, t_data **data)
{
	if (keycode == 53)
		close_win((*data));
	if (keycode == S_KEY)
		(*data)->player->walk_direction = -1;
	if (keycode == W_KEY)
		(*data)->player->walk_direction = 1;
	if (keycode == LEFT_ARROW)
		(*data)->player->turn_direction = 1;
	if (keycode == RIGHT_ARROW)
		(*data)->player->turn_direction = -1;
	if (keycode == D_KEY)
	{
		(*data)->player->walk_direction = -1;
		(*data)->player->side_angle = 90;
	}
	if (keycode == A_KEY)
	{
		(*data)->player->walk_direction = 1;
		(*data)->player->side_angle = 90;
	}
	return (0);
}
