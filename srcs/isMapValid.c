#include "cub3D.h"

void isSpaceValid(t_lst *line, char **curr,int i)
{
	char *prev;
	char *next;

	if(line->previous)
	{
		prev = line->previous->content;
		if(ONE_OR_SPACE(prev[i]) && ONE_OR_SPACE(*curr[i-1]) && ONE_OR_SPACE(*curr[i+1]))
			(*curr)[i] = '1';
		else
			ErrorMessage("Invalid map");
	}
	if(line->next)
	{
		next = line->next->content;
		if(ONE_OR_SPACE(next[i]) && ONE_OR_SPACE(*curr[i-1]) && ONE_OR_SPACE(*curr[i+1]))
			(*curr)[i] = '1';
		else
			ErrorMessage("Invalid map");
	}
}

t_lst *WallCheck(t_lst *Wall)
{
	int i = 1;
	char *line = Wall->content;
	while(line[i+1])
	{
		if(line[i] != '1')
		{
			if(ft_isspace(line[i]))
				isSpaceValid(Wall, (char **)&(Wall)->content, i);
			else
				ErrorMessage("Invalid map.");
		}
		i++;
	}
	return(Wall->next);
}


void isMapValid(t_lst **maphead)
{
	t_lst *map;

	map = (*maphead);
	map = WallCheck(map);
	while(map->next)
	{
		printf("other walls %s\n", map->content);
		map = map->next;
	}
	//check for first wall
	//check for first and last character
	//check for what's inside the walls
	//check for last wall
}