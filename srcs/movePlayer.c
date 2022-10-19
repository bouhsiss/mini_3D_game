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


int keyrelease(int keycode, t_data **data)
{
	int *turndirection = &(*data)->player->turnDirection;
	int *walkdirection = &(*data)->player->walkDirection;
	double *sideAngle = &(*data)->player->sideAngle;
	if(keycode == 53)
		closeWin((*data));
	if(keycode == S_KEY)
		*walkdirection = 0;
	if(keycode == W_KEY)
		*walkdirection = 0;
	if(keycode == LEFT_ARROW)
		*turndirection = 0;
	if(keycode == RIGHT_ARROW)
		*turndirection = 0;
	if(keycode == D_KEY)
	{
		*walkdirection = 0;
		*sideAngle = 0;	
	}
	if(keycode == A_KEY)
	{
		*walkdirection = 0;
		*sideAngle = 0;	
	}
	return(0);
}

int movePlayer(int keycode, t_data **data)
{
	int *turndirection = &(*data)->player->turnDirection;
	int *walkdirection = &(*data)->player->walkDirection;
	double *sideAngle = &(*data)->player->sideAngle;
	if(keycode == 53)
		closeWin((*data));
	if(keycode == S_KEY)
		*walkdirection = -1;
	if(keycode == W_KEY )
		*walkdirection = 1;
	if(keycode == LEFT_ARROW)
		*turndirection = 1;
	if(keycode == RIGHT_ARROW)
		*turndirection = -1;
	if(keycode == D_KEY)
	{
		*walkdirection = -1;
		*sideAngle = 90;	
	}
	if(keycode == A_KEY)
	{
		*walkdirection = 1;
		*sideAngle = 90;	
	}
	return(0);
}
