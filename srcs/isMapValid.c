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

int	check_map_is_valid(t_data **data)
{
	t_lst *prev_node;
	t_lst *curr_node;
	char *curr_line;
	char *prev_line;
	int	i;

	i = 0;
	prev_node = (*data)->MapDisplay->map;
	curr_node = (*data)->MapDisplay->map;
	while (curr_node)
	{
		curr_line = (char *)curr_node->content;
		prev_line = (char *)prev_node->content;
		while (curr_line[i])
		{
			if((curr_line[i] == '0' && (  ft_strlen(prev_line) - 2 < i || prev_line[i] == ' ')))
				ErrorMessage("Invalid map.");
			/*
				once a space is found -> check whether is surrounded by ones
			*/
			i++;
		}
		i = 0;
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	return 0;
}