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
	(*data)->mapdisplay = (t_map *)malloc(sizeof(t_map));
	(*data)->mapdisplay->text_paths = malloc(sizeof(t_text_path));
	(*data)->win = (t_win *)malloc(sizeof(t_win));
	(*data)->mapdisplay->ceiling_color = (t_colors *)malloc(sizeof(t_colors));
	(*data)->mapdisplay->floor_color = (t_colors *)malloc(sizeof(t_colors));
	(*data)->win->win_img = (t_img *)malloc(sizeof(t_img));
	(*data)->mapdisplay->wall = (t_img *)malloc(sizeof(t_img));
	(*data)->mapdisplay->wall_2 = (t_img *)malloc(sizeof(t_img));
	(*data)->player = (t_player *)malloc(sizeof(t_player));
	(*data)->mapdisplay->ray = (t_ray *)malloc(sizeof(t_ray));
	(*data)->mapdisplay->text_imgs = (t_text_img *)malloc(sizeof(t_text_img));
	(*data)->mapdisplay->text_imgs->north = (t_img *)malloc(sizeof(t_img));
	(*data)->mapdisplay->text_imgs->south = (t_img *)malloc(sizeof(t_img));
	(*data)->mapdisplay->text_imgs->west = (t_img *)malloc(sizeof(t_img));
	(*data)->mapdisplay->text_imgs->east = (t_img *)malloc(sizeof(t_img));
}

void	constructor(t_data **data)
{
	heap_allocation(data);
	(*data)->mapdisplay->text_paths->north = NULL;
	(*data)->mapdisplay->text_paths->south = NULL;
	(*data)->mapdisplay->text_paths->west = NULL;
	(*data)->mapdisplay->text_paths->east = NULL;
	(*data)->mapdisplay->ceiling_color->flag = false;
	(*data)->mapdisplay->floor_color->flag = false;
	(*data)->mapdisplay->columns_nbr = 0;
	(*data)->mapdisplay->rows_nbr = 0;
	(*data)->mapdisplay->map = NULL;
	(*data)->player->turn_direction = 0;
	(*data)->player->walk_direction = 0;
	(*data)->player->side_angle = 0;
	(*data)->player->move_speed = 15;
	(*data)->player->rotation_speed = 4 * DEGREE;
}
