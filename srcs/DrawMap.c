#include "cub3D.h"
 
/*
createRGB(23, 23, 23); // wall
createRGB(115, 113, 113); //floor
createRGB(218, 0, 55); // player
*/

/*
createRGB(23, 23, 23); // wall
createRGB(115, 113, 113); //floor
createRGB(218, 0, 55); // player
7171
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


void putSquareInImage(t_data **data, int x, int y, unsigned long color)
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
			my_mlx_pixel_put((*data)->img, x, y, color);
			x++;
		}
		y++;
	}
}

void drawWall(t_data **data)
{
	int x;
	int y;

	y = -1;
	while(++y < RESOLUTION * (*data)->MapDisplay->NbrOfRows)
	{
		x = -1;
		while(++x < RESOLUTION * (*data)->MapDisplay->NbrOfColumns)
			my_mlx_pixel_put((*data)->img, x, y, createRGB(23, 23, 23));
	}
}

void drawLine(t_data **data,int beginX, int beginY, int endX, int endY)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = beginX;
	double pixelY = beginY;
	while(pixels)
	{
		my_mlx_pixel_put((*data)->img->img, pixelX, pixelY, createRGB(218, 0, 55));
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

 
void DDA(t_data **data, int X1, int Y1)
{
    int dx = X1 - (*data)->player->x;
    int dy = Y1 - (*data)->player->y;
 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    float X = (*data)->player->x;
    float Y = (*data)->player->y;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put((*data)->img, X, Y,createRGB(218, 0, 55));
        X += Xinc;
        Y += Yinc;
    }
}

void drawPlayer(t_data **data)
{
	double angle;
	int color;

	double x;
	double y;
	int radius = RADIUS;
	color = createRGB(218, 0, 55);
	angle = 0;
	while(angle <= 360)
	{
		x = radius * cos(angle);
		y = radius * sin(angle);
		DDA(data,(*data)->player->x + x, (*data)->player->y + y);
		angle += 0.01f;
	}
	DDA(data, (*data)->player->x + ((LINE_LENGTH)*cos((*data)->player->initialAngle)), (*data)->player->y + ((LINE_LENGTH)*sin((*data)->player->initialAngle)));
}



void drawMiniMap(t_data **Data, t_lst **map)
{
	int x;
	int y;
	int j = 0;
	int i;
	char *line;
	t_lst *tmp = (*map);

	y = 0;
	drawWall(Data);
	while (tmp)
	{
		i = -1;
		x = 0;
		line = tmp->content;
		while(line[++i])
		{
			if(line[i] == 'N' || line[i] == 'E' || line[i] == 'W' || line[i] == 'S' || line[i] == '0')
				putSquareInImage(Data, x , y, createRGB(115, 113, 113));
			x += RESOLUTION;
		}
		y += RESOLUTION;
		j++;
		tmp = tmp->next;
	}
	
	drawPlayer(Data);
	mlx_put_image_to_window((*Data)->mlx_ptr, (*Data)->win->mlx_win, (*Data)->img->img, 0, 0);
}



void DrawMap(t_data **Data)
{
	(*Data)->mlx_ptr = mlx_init();
	(*Data)->win->mlx_win = mlx_new_window((*Data)->mlx_ptr, (*Data)->MapDisplay->NbrOfColumns * RESOLUTION, (*Data)->MapDisplay->NbrOfRows * RESOLUTION, "SmolWolf3D");
	mlx_hook((*Data)->win->mlx_win, 17, 1L << 5, closeWin, (*Data));
	(*Data)->img->img = mlx_new_image((*Data)->mlx_ptr, RESOLUTION * (*Data)->MapDisplay->NbrOfColumns, \
	RESOLUTION * (*Data)->MapDisplay->NbrOfRows);
	(*Data)->img->addr = mlx_get_data_addr((*Data)->img->img, &((*Data)->img->bits_per_pixel), &((*Data)->img->line_length),\
	 &((*Data)->img->endian));
	drawMiniMap(Data,  &(*Data)->MapDisplay->map);
	mlx_hook((*Data)->win->mlx_win, 02,  1L << 0, movePlayer, Data);
	mlx_hook((*Data)->win->mlx_win, 03, 1L << 0, keyrelease, Data);
	mlx_loop((*Data)->mlx_ptr);
}

//gotta implement an mlx loop hook function to synchronize player movement
// and implement a function to update x and y and check whether the next cell has a wall or not 
// based on the walk direction .....