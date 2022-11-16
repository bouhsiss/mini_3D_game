/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:02:50 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/16 21:02:52 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_in_window(t_data **data)
{
	draw_background(data);
	draw_minimap(data);
	move_player(data, &(*data)->player);
	cast_rays(*data);
	draw_player(data);
	mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win->mlx_win, \
	(*data)->win->win_img->img, 0, 0);
}

void	update_window(t_data **data)
{
	(*data)->player->initial_angle += (*data)->player->turn_direction * \
		(*data)->player->rotation_speed;
	draw_in_window(data);
}

int	handler(t_data **data)
{
	mlx_hook((*data)->win->mlx_win, 17, 1L << 5, close_win, (*data));
	mlx_hook((*data)->win->mlx_win, 02, 1L << 0, key_press, data);
	mlx_hook((*data)->win->mlx_win, 03, 1L << 1, keyrelease, data);
	mlx_hook((*data)->win->mlx_win, 04, 1L << 2, button_press, data);
	mlx_hook((*data)->win->mlx_win, 05, 1L << 3, button_release, data);
	update_window(data);
	return (0);
}

void	init_imgs(t_data *data)
{
	data->mapdisplay->text_imgs->north->img = \
		create_img(data, data->mapdisplay->text_paths->north);
	data->mapdisplay->text_imgs->south->img = \
		create_img(data, data->mapdisplay->text_paths->south);
	data->mapdisplay->text_imgs->west->img = \
		create_img(data, data->mapdisplay->text_paths->west);
	data->mapdisplay->text_imgs->east->img = \
		create_img(data, data->mapdisplay->text_paths->east);
}

void	init_game_loop(t_data **data)
{
	t_img	*img;

	img = (*data)->win->win_img;
	(*data)->mlx_ptr = mlx_init();
	init_imgs(*data);
	(*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT, "SmolWolf3D");
	(*data)->win->win_img->img = mlx_new_image((*data)->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT);
	(*data)->win->win_img->addr = mlx_get_data_addr(img->img, \
	&(img->bits_per_pixel), &(img->line_length), &(img->endian));
	draw_in_window(data);
	mlx_loop_hook((*data)->mlx_ptr, handler, data);
	mlx_loop((*data)->mlx_ptr);
}
