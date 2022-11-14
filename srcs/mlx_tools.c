#include "cub3D.h"

void draw_in_window(t_data **data)
{
	draw_background(data, 0xc7b09a, 0x5b75a6);
	// draw_minimap(data);
	move_player(data, &(*data)->player);
	cast_rays(*data);
	draw_player(data);
	mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win->mlx_win, \
	(*data)->img->img, 0, 0);
}

void update_window(t_data **data)
{
	(*data)->player->initialAngle += (*data)->player->turnDirection * \
		(*data)->player->rotationSpeed;
	(*data)->player->initialAngle = fmod(2*PI + fmod((*data)->player->initialAngle, 2*PI), 2*PI);
	draw_in_window(data);
}

int button_press(int button_code, int x, int y, t_data **data)
{
	(void)y;
	(void)x;
	if(button_code == 1)
		(*data)->player->turnDirection = -1;
	if(button_code == 2)
		(*data)->player->turnDirection = 1;
	return(0);
}

int button_release(int button_code, int x, int y, t_data **data)
{
	(void)y;
	(void)x;
	if(button_code == 1)
		(*data)->player->turnDirection = 0;
	if(button_code == 2)
		(*data)->player->turnDirection = 0;
	return(1);
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

void	init_mlx_loop(t_data **data)
{
	(*data)->mlx_ptr = mlx_init();
	(*data)->MapDisplay->wall->img = create_img((*data), "./wall.xpm");
	(*data)->MapDisplay->wall_2->img = create_img((*data), "./wall_2.xpm");
	// (*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
	// 	(*data)->MapDisplay->NbrOfColumns * MINIMAP_TILE_SIZE, \
	// 	(*data)->MapDisplay->NbrOfRows * MINIMAP_TILE_SIZE, "SmolWolf3D");
	(*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT, "SmolWolf3D");
	// (*data)->img->img = mlx_new_image((*data)->mlx_ptr, \
	// 	MINIMAP_TILE_SIZE * (*data)->MapDisplay->NbrOfColumns, \
	// 	MINIMAP_TILE_SIZE * (*data)->MapDisplay->NbrOfRows);
	(*data)->img->img = mlx_new_image((*data)->mlx_ptr,WINDOW_WIDTH, WINDOW_HEIGHT);
	(*data)->img->addr = mlx_get_data_addr((*data)->img->img, \
		&((*data)->img->bits_per_pixel), &((*data)->img->line_length), \
		&((*data)->img->endian));
	draw_in_window(data);
	mlx_loop_hook((*data)->mlx_ptr, handler, data);
	mlx_loop((*data)->mlx_ptr);
}
