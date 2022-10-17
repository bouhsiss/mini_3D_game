#include "cub3D.h"

void constructor(t_data **Data)
{
	(*Data) = (t_data *)malloc(sizeof(t_data));
	(*Data)->MapDisplay = (t_map *)malloc(sizeof(t_map));
	(*Data)->MapDisplay->textures = (t_textures *)malloc(sizeof(t_textures));
	(*Data)->win = (t_win *)malloc(sizeof(t_win));
	(*Data)->MapDisplay->CeilingColor = (t_colors *)malloc(sizeof(t_colors));
	(*Data)->MapDisplay->FloorColor = (t_colors *)malloc(sizeof(t_colors));
	(*Data)->img = (t_img *)malloc(sizeof(t_img));
	(*Data)->player = (t_player *)malloc(sizeof(t_player));
	/* == heap allocation == */

	(*Data)->MapDisplay->NbrOfColumns = 0;
	(*Data)->MapDisplay->NbrOfRows = 0;
	(*Data)->MapDisplay->map = NULL;
	// (*Data)->player->x = 300; // i * RESOLUTION + (RESOLUTION/2)
	// (*Data)->player->y = 140; // j * RESOLUTION + (RESOLUTION/2)
	(*Data)->player->turnDirection = 0;
	(*Data)->player->walkDirection = 0;
	(*Data)->player->initialAngle = NORTH + (FOV/2);
	(*Data)->player->moveSpeed = 5;
	(*Data)->player->rotationSpeed = 10*DEGREE;
	//code to construct/initialize my struct
}

//implement hooks and to turn the player :
// update the rotation angle by incrementing it by (turndirection * rotationspeed)'

//implement hooks to move the player :
//update the x and y by incrementing it by (cos and sin of rotaion angle *(walkdirection * move speed))