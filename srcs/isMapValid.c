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
		ErrorMessage("am here ===== 1");
	else if( ft_strlen(prev_line) - 2 > i && ((ft_isspace(prev_line[i]) && is_valid_char(prev_line[i -1])) || ((is_valid_char(prev_line[i])  
		&& ( ft_isspace(prev_line[i - 1]) || ft_strlen(curr_line) - 2 < i || ft_isspace(curr_line[i]))))))
			ErrorMessage("am here ===== 2");
	else if( !is_valid_char(curr_line[i]) && curr_line[i] != '1' && !ft_isspace(curr_line[i]))
		ErrorMessage("am here ===== 3");
	return(0);
}

int	check_map_is_valid(t_data **data)
{
	t_lst *prev_node;
	t_lst *curr_node;
	char *curr_line;
	char *prev_line;
	int	i;
	int flag;

	flag = 0;
	i = 0;
	prev_node = (*data)->MapDisplay->map;
	curr_node = (*data)->MapDisplay->map;
	if(check_first_and_last_line((char *) prev_node->content))
		ErrorMessage("Invalid map.");
	while (curr_node)
	{
		curr_line = (char *)curr_node->content;
		prev_line = (char *)prev_node->content;
			printf("%s",curr_line);
		i = ft_strlen(curr_line) -1;
		while (i)
		{
			if(curr_line[i] == 'N' || curr_line[i] == 'S' || curr_line[i] == 'E' || curr_line[i] == 'W')
				flag++;
			if (check_two_line(curr_line, prev_line, i) || flag > 1)
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