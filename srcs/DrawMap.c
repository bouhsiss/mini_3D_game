#include "cub3D.h"
 
/*
createRGB(98, 142, 144); // wall
createRGB(245, 239, 230); //floor
createRGB(60, 35, 23); // player
*/


unsigned long createRGB(int r, int g, int b)
{
	return(((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF)));
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void putSquareInImage(t_data **Data, int x, int y, unsigned long color)
{
	int i = 0;
	int j;
	int tmp_x = x;
	while(++i < RESOLUTION )
	{
		x = tmp_x;
		j = 0;
		while(++j < RESOLUTION )
		{
			my_mlx_pixel_put((*Data)->img, x, y, color);
			x++;
		}
		y++;
	}
}

void createWallImage(t_data **Data)
{
	int x;
	int y;

	y = -1;
	while(++y < RESOLUTION * (*Data)->MapDisplay->NbrOfRows)
	{
		x = -1;
		while(++x < RESOLUTION * (*Data)->MapDisplay->NbrOfColumns)
			my_mlx_pixel_put((*Data)->img, x, y, createRGB(98, 142, 144));
	}
}

void drawMap(t_data **Data, t_lst **map)
{
	int x;
	int y;
	int i;
	char *line;

	y = 0;
	(*Data)->img->img = mlx_new_image((*Data)->mlx_ptr, RESOLUTION * (*Data)->MapDisplay->NbrOfColumns, \
	RESOLUTION * (*Data)->MapDisplay->NbrOfRows);
	(*Data)->img->addr = mlx_get_data_addr((*Data)->img->img, &((*Data)->img->bits_per_pixel), &((*Data)->img->line_length),\
	 &((*Data)->img->endian));
	createWallImage(Data);
	while ((*map))
	{
		i = 0;
		x = 0;
		line = (*map)->content;
		while(line[i])
		{
			if(line[i] == '0' )
				putSquareInImage(Data, x , y, createRGB(245, 239, 230));
			if(line[i] == 'N' || line[i] == 'E' || line[i] == 'W' || line[i] == 'S')
			{
				putSquareInImage(Data, x , y, createRGB(245, 239, 230));
				(*Data)->player->x = (RESOLUTION /2) + x;
				(*Data)->player->y = (RESOLUTION /2) + y;
			}
			x += RESOLUTION;
			i++;
		}
		y += RESOLUTION;
		(*map) = (*map)->next;
	}
	mlx_put_image_to_window((*Data)->mlx_ptr, (*Data)->win->mlx_win, (*Data)->img->img, 0, 0);
}

void drawPlayer(t_data **Data)
{
	double angle;
	int color;

	angle = 0;
	int x;
	int y;
	int radius = RADIUS;
	color = createRGB(60, 35, 23);
	while(radius)
	{
		angle = 0;
		while(angle <= 360)
		{
			x = radius * cos(angle);
			y = radius * sin(angle);
			my_mlx_pixel_put((*Data)->img, (*Data)->player->x + x, (*Data)->player->y + y, color);
			angle += 0.01f;
		}
		radius--;
	}
	mlx_put_image_to_window((*Data)->mlx_ptr, (*Data)->win->mlx_win, (*Data)->img->img, 0, 0);
}

void DrawMap(t_data **Data)
{
	(*Data)->mlx_ptr = mlx_init();
	(*Data)->win->mlx_win = mlx_new_window((*Data)->mlx_ptr, (*Data)->MapDisplay->NbrOfColumns * RESOLUTION, (*Data)->MapDisplay->NbrOfRows * RESOLUTION, "SmolWolf3D");
	mlx_hook((*Data)->win->mlx_win, 17, 1L << 5, closeWin, (*Data));
	drawMap(Data,  &(*Data)->MapDisplay->map);
	drawPlayer(Data);
	mlx_loop((*Data)->mlx_ptr);
}