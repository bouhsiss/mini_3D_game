/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:08 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/06 22:49:31 by omeslall         ###   ########.fr       */
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
	(*data)->MapDisplay->wall = (t_img *)malloc(sizeof(t_img));
	(*data)->MapDisplay->wall_2 = (t_img *)malloc(sizeof(t_img));
	(*data)->player = (t_player *)malloc(sizeof(t_player));
	(*data)->MapDisplay->ray = (t_ray *)malloc(sizeof(t_ray));
}

void	constructor(t_data **data)
{
	heap_allocation(data);
	(*data)->MapDisplay->NbrOfColumns = 0;
	(*data)->MapDisplay->NbrOfRows = 0;
	(*data)->MapDisplay->map = NULL;
	(*data)->win->mouse_pointer_x = 0;
	(*data)->player->turnDirection = 0;
	(*data)->player->walkDirection = 0;
	(*data)->player->sideAngle = 0;
	(*data)->player->moveSpeed = 10;
	(*data)->player->rotationSpeed = 5 * DEGREE;
}
