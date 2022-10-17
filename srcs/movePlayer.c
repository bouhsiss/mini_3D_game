#include "cub3D.h"


int keyrelease(int keycode, t_data **data)
{
	int *turndirection = &(*data)->player->turnDirection;
	int *walkdirection = &(*data)->player->walkDirection;
	if(keycode == 53)
		closeWin((*data));
	if(keycode == S_KEY)
		*walkdirection = 0;
	if(keycode == W_KEY)
		*walkdirection = 0;
	if(keycode == LEFT_ARROW)
		*turndirection = 0;
	if(keycode == RIGHT_ARROW)
		*turndirection = 0;
	return(0);
}

int checkWallCollision(t_data **data)
{
	int i;
	int j;
	t_lst *map;
	char *content;

	i = ((*data)->player->x )/ RESOLUTION;
	j = ((*data)->player->y )/ RESOLUTION;
	map = (*data)->MapDisplay->map;
	printf("i == %d j === %d \n", i, j);
	while(j)
	{
		map = map->next;
		j--;
	}
	content = map->content;
	printf("cell == %c\n", content[i]);
	printf("x == %d y === %d \n",(*data)->player->x,  (*data)->player->y);
	return(1);
}

//gotta redo all this ...

int movePlayer(int keycode, t_data **data)
{
	int *turndirection = &(*data)->player->turnDirection;
	int *walkdirection = &(*data)->player->walkDirection;

	float side = 0;
	if(keycode == 53)
		closeWin((*data));
	if(keycode == S_KEY)
		*walkdirection = -1;
	if(keycode == W_KEY)
		*walkdirection = 1;
	if(keycode == LEFT_ARROW)
		*turndirection = 1;
	if(keycode == RIGHT_ARROW)
		*turndirection = -1;
	if(keycode == D_KEY)
	{
		*walkdirection = 1;
		side = 90;	
	}
	if(keycode == A_KEY)
	{
		*walkdirection = -1;
		side = 90;	
	}
	(*data)->player->initialAngle += (*data)->player->turnDirection * (*data)->player->rotationSpeed;
	(*data)->player->x += cos((*data)->player->initialAngle + side*DEGREE) * ((*data)->player->walkDirection * ((*data)->player->moveSpeed)) ;
	(*data)->player->y += sin((*data)->player->initialAngle + side*DEGREE) * ((*data)->player->walkDirection * ((*data)->player->moveSpeed)) ;
	checkWallCollision(data);
	drawMiniMap(data, &(*data)->MapDisplay->map);
	return(0);
}
