#include "cub3D.h"

int closeWin(t_data *Data)
{
	mlx_destroy_window(Data->mlx_ptr, Data->win->mlx_win);
	ft_lstdelete(&Data->MapDisplay->map);
	exit(0);
}