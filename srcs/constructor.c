/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:08 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:01:12 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void constructor(t_data **Data)
{
	(*Data) = (t_data *)malloc(sizeof(t_data));
	(*Data)->MapDisplay = (t_map *)malloc(sizeof(t_map));
	(*Data)->MapDisplay->textures = (t_textures *)malloc(sizeof(t_textures));
	(*Data)->win = (t_win *)malloc(sizeof(t_win));
	(*Data)->MapDisplay->CeilingColor = (t_colors *)malloc(sizeof(t_colors));
	(*Data)->MapDisplay->FloorColor = (t_colors *)malloc(sizeof(t_colors));
	(*Data)->img = (t_img *)malloc(sizeof(t_img));
	(*Data)->player = (t_player *)malloc(sizeof(t_player));
	/* == heap allocation == */

	(*Data)->MapDisplay->NbrOfColumns = 0;
	(*Data)->MapDisplay->NbrOfRows = 0;
	(*Data)->MapDisplay->map = NULL;
	(*Data)->player->turnDirection = 0;
	(*Data)->player->walkDirection = 0;
	(*Data)->player->initialAngle = NORTH + (FOV/2);
	(*Data)->player->sideAngle = 0;
	(*Data)->player->moveSpeed = 3;
	(*Data)->player->rotationSpeed = 3*DEGREE;
}

//implement hooks and to turn the player :
// update the rotation angle by incrementing it by (turndirection * rotationspeed)'

//implement hooks to move the player :
//update the x and y by incrementing it by (cos and sin of rotaion angle *(walkdirection * move speed))

// x = j * Resolution + (resolution/2)
// i = (x - (Resolution/ 2) ) / resolution
