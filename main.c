#include "cub3D.h"

int main(int ac, char **av){
	t_data *Data;

	if(ac == 2)
	{
		constructor(&Data);
		Parser(av[1], &Data);
		ft_lstdelete(&Data->MapDisplay->map);
		// system("Leaks cub3D");
	}
	else
		ErrorMessage("Usage : ./cub3D < .cub map file >");
}