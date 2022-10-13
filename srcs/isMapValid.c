#include "cub3D.h"

int	skip_space(char *str)
{
	int i;

	i = 0;
	while(str && ft_isspace(str[i]))
		i++;
	return(i);
}

int	check_previous(char *previous,int len)
{
	int i = 0;
	if ( previous[ft_strlen(previous) - 2] == '1' && previous[skip_space(previous)] == '1')
		return(0);
	else
	{
		// previous = previous + len;
		while (previous[i])
		{
			if(previous[i] == '0' && i > len - 2)
				return(1);
			i++;
		}
	}
	return(1);
}

int check_first_and_last_line(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if(line[i] == '0')
			return(1);
	}
	return(0);
}

int check_two_line(char *curr_line,char *prev_line , int i)
{
	if( (curr_line[i] == ' ' && curr_line[i -1] == '0') || ((curr_line[i] == '0'  
		&& ( curr_line[i - 1] == ' ' || ft_strlen(prev_line) - 2 < i || prev_line[i] == ' '))))
		return(1);
	else if(( (prev_line[i] == ' ' && prev_line[i -1] == '0') || ((prev_line[i] == '0'  
		&& ( prev_line[i - 1] == ' ' || ft_strlen(curr_line) - 2 < i || curr_line[i] == ' ')))))
		return(1);
	return(0);
}

int	check_map_is_valid(t_data **data)
{
	t_lst *prev_node;
	t_lst *curr_node;
	char *curr_line;
	char *prev_line;
	int	i;
	int position;

	position = 0;
	i = 0;
	prev_node = (*data)->MapDisplay->map;
	curr_node = (*data)->MapDisplay->map;
	if(check_first_and_last_line((char *) prev_node->content))
		ErrorMessage("Invalid map.");
	while (curr_node)
	{
		curr_line = (char *)curr_node->content;
		prev_line = (char *)prev_node->content;
		i = ft_strlen(curr_line) - 1;
		while (i > 0)
		{
			if(curr_line[i] == 'N' || curr_line[i] == 'S' || curr_line[i] == 'E' || curr_line[i] == 'W')
				position++;
			if (check_two_line(curr_line, prev_line, i) || position > 1)
				ErrorMessage("Invalid map.");
			i--;
		}
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	if(check_first_and_last_line(curr_line))
		ErrorMessage("Invalid map.");
	return 0;
}