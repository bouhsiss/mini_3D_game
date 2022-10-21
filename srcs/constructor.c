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

void	heap_allocation(t_data **data)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->MapDisplay = (t_map *)malloc(sizeof(t_map));
	(*data)->MapDisplay->textures = (t_textures *)malloc(sizeof(t_textures));
	(*data)->win = (t_win *)malloc(sizeof(t_win));
	(*data)->MapDisplay->CeilingColor = (t_colors *)malloc(sizeof(t_colors));
	(*data)->MapDisplay->FloorColor = (t_colors *)malloc(sizeof(t_colors));
	(*data)->img = (t_img *)malloc(sizeof(t_img));
	(*data)->player = (t_player *)malloc(sizeof(t_player));
}

void	constructor(t_data **data)
{
	heap_allocation(data);
	(*data)->MapDisplay->NbrOfColumns = 0;
	(*data)->MapDisplay->NbrOfRows = 0;
	(*data)->MapDisplay->map = NULL;
	(*data)->player->turnDirection = 0;
	(*data)->player->walkDirection = 0;
	(*data)->player->sideAngle = 0;
	(*data)->player->moveSpeed = 3;
	(*data)->player->rotationSpeed = 3 * DEGREE;
}
