#include "cub3D.h"

int main(int ac, char **av){
	t_data *Data;

	Data = (t_data *)malloc(sizeof(t_data));
	Data->textures = (t_textures *)malloc(sizeof(t_textures));
	Data->win = (t_win *)malloc(sizeof(t_win));
	if(ac == 2)
	{
		Parser(av[1], &Data);
		system("Leaks cub3D");
	}
	else
		ErrorMessage("Usage : ./cub3D < .cub map file >");
}