#include "cub3D.h"

int	close_win(t_data *Data)
{
	mlx_destroy_window(Data->mlx_ptr, Data->win->mlx_win);
	free_array((*Data).MapDisplay->map);
	// system("leaks cub3D");
	exit(0);
}

int	handler(t_data **data)
{
	mlx_hook((*data)->win->mlx_win, 17, 1L << 5, close_win, (*data));
	mlx_hook((*data)->win->mlx_win, 02, 1L << 0, key_press, data);
	mlx_hook((*data)->win->mlx_win, 03, 1L << 1, keyrelease, data);
	(*data)->player->initialAngle += (*data)->player->turnDirection * \
		(*data)->player->rotationSpeed;
	(*data)->player->initialAngle = fmod(2*PI + fmod((*data)->player->initialAngle, 2*PI), 2*PI);
	draw_background(data, 0x9b7653, 0x87ceeb);
	draw_mini_map(data);
	move_player(data, &(*data)->player);
	render_map(data);
	draw_player(data);
	mlx_put_image_to_window((*data)->mlx_ptr, (*data)->win->mlx_win, \
	(*data)->img->img, 0, 0);
	return (0);
}

void init_mlx_loop(t_data **data)
{	
	(*data)->mlx_ptr = mlx_init();
	// (*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
	// 	(*data)->MapDisplay->NbrOfColumns * MINI_MAP_TILE_SIZE, \
	// 	(*data)->MapDisplay->NbrOfRows * MINI_MAP_TILE_SIZE, "SmolWolf3D");
	(*data)->win->mlx_win = mlx_new_window((*data)->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT, "SmolWolf3D");
	// (*data)->img->img = mlx_new_image((*data)->mlx_ptr, \
	// 	MINI_MAP_TILE_SIZE * (*data)->MapDisplay->NbrOfColumns, \
	// 	MINI_MAP_TILE_SIZE * (*data)->MapDisplay->NbrOfRows);
	(*data)->img->img = mlx_new_image((*data)->mlx_ptr,WINDOW_WIDTH, WINDOW_HEIGHT);
	(*data)->img->addr = mlx_get_data_addr((*data)->img->img, \
		&((*data)->img->bits_per_pixel), &((*data)->img->line_length), \
		&((*data)->img->endian));
	mlx_loop_hook((*data)->mlx_ptr, handler, data);
	mlx_loop((*data)->mlx_ptr);
}