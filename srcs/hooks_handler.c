#include "cub3D.h"

void checkWallCollision(t_data **data)
{
	int nextPosX;
	int nextPosY;
	int i;
	int j;
	t_lst *map = (*data)->MapDisplay->map;
	char *content;
	int walkdir = (*data)->player->walkDirection;
	nextPosX = (*data)->player->x + (cos((*data)->player->initialAngle  + (*data)->player->sideAngle*DEGREE) * (walkdir * (((*data)->player->moveSpeed) + RADIUS)));
	nextPosY = (*data)->player->y + (sin((*data)->player->initialAngle  + (*data)->player->sideAngle*DEGREE) * (walkdir * (((*data)->player->moveSpeed) + RADIUS)));
	i = nextPosX / RESOLUTION;
	j = nextPosY / RESOLUTION;
	while(j)
	{
		map = map->next;
		j--;
	}
	content = map->content;
	if(content[i] != '1')
	{
		(*data)->player->x += (cos((*data)->player->initialAngle  + (*data)->player->sideAngle*DEGREE) * ((*data)->player->walkDirection * ((*data)->player->moveSpeed))) ;
		(*data)->player->y +=  (sin((*data)->player->initialAngle  + (*data)->player->sideAngle*DEGREE) * ((*data)->player->walkDirection * ((*data)->player->moveSpeed)));
	}
}

int handler(t_data **data)
{
	mlx_hook((*data)->win->mlx_win, 17, 1L << 5, closeWin, (*data));
	mlx_hook((*data)->win->mlx_win, 02, 1L << 0, movePlayer, data);
	mlx_hook((*data)->win->mlx_win, 03, 1L << 1, keyrelease, data);
	(*data)->player->initialAngle += (*data)->player->turnDirection * (*data)->player->rotationSpeed;
	checkWallCollision(data);
	drawMiniMap(data, &(*data)->MapDisplay->map);
	return(0);
}  