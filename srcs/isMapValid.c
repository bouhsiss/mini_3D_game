#include "cub3D.h"

int	skip_space(char *str)
{
	int i;

	i = 0;
	while(str && ft_isspace(str[i]))
		i++;
	return(i);
}

int	is_valid_char(char c)
{
	if ( c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '0')
		return(1);
	return(0);
}

int check_first_and_last_line(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if(is_valid_char(line[i]))
			return(1);
	}
	return(0);
}


int check_two_line(char *curr_line,char *prev_line , int i)
{
	if( (ft_isspace(curr_line[i]) && is_valid_char(curr_line[i -1])) || ((is_valid_char(curr_line[i])  
		&& ( ft_isspace(curr_line[i - 1])|| ft_strlen(prev_line) - 2 < i || ft_isspace(prev_line[i])))))
		error_message("Invalid map.4");
	else if( ft_strlen(prev_line) - 2 > i && ((ft_isspace(prev_line[i]) && is_valid_char(prev_line[i -1])) || ((is_valid_char(prev_line[i])  
		&& ( ft_isspace(prev_line[i - 1]) || ft_strlen(curr_line) - 2 < i || ft_isspace(curr_line[i]))))))
			error_message("Invalid map 5");
	else if( !is_valid_char(curr_line[i]) && curr_line[i] != '1' && !ft_isspace(curr_line[i]))
		error_message("Invalid map 6");
	return(0);
}

int savePlayerPos(int i, int j, t_data **data, char c)
{
	(*data)->player->x = i * RESOLUTION + (RESOLUTION / 2);
	(*data)->player->y = j * RESOLUTION + (RESOLUTION / 2);
	if(c == 'N')
		(*data)->player->initialAngle = NORTH;
	if(c == 'S')
		(*data)->player->initialAngle = SOUTH;
	if(c == 'E')
		(*data)->player->initialAngle = EAST;
	if(c == 'W')
		(*data)->player->initialAngle = WEST;
	return(1);
}

int	check_map_is_valid(t_data **data)
{
	char *curr_line;
	char *prev_line;
	int	i;
	int curr;
	int prev;
	int flag;

	flag = 0;
	curr = 0;
	prev = 0;
	if(check_first_and_last_line((*data)->MapDisplay->map[prev]))
		error_message("Invalid map.1");
	while ((*data)->MapDisplay->map[curr])
	{
		curr_line = (*data)->MapDisplay->map[curr];
		prev_line = (*data)->MapDisplay->map[prev];
		i = ft_strlen(curr_line) -1;
		while (i)
		{
			if(curr_line[i] == 'N' || curr_line[i] == 'S' || curr_line[i] == 'E' || curr_line[i] == 'W')
				flag += savePlayerPos(i, curr, data, curr_line[i]);
			if (check_two_line(curr_line, prev_line, i) || flag > 1)
				error_message("Invalid map.2");
			i--;
		}
		prev = curr;
		curr++;
	}
	if(check_first_and_last_line(curr_line) || flag == 0)
		error_message("Invalid map.3");
	return 0;
}