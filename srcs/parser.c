#include "cub3D.h"

static int open_file(char *MapPath) {
	int fd;

	if(open(MapPath, O_DIRECTORY) > 0)
		ErrorMessage("map should be a file not a directory.");
	if(ft_strncmp(ft_strchr(MapPath,'.'), ".cub", 4))
		ErrorMessage("map should have .cub extension");
	fd = open(MapPath, O_RDONLY);
	if(fd == -1)
		ErrorMessage(strerror(errno));
	return(fd);
}

int parseTexture(char *line, char **Data)
{
	int i = 0;
	while(ft_isspace(line[i]))
		i++;
	(*Data) = ft_substr(line, i, ft_strlen(line) - i + 1);
	return(1);
}

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

int	check_line_is_valid(t_data **data)
{
	t_lst *previous;
	t_lst *tmp;
	char *tmp_str1;
	char *tmp_str2;
	int	i;

	i = 0;
	previous = (*data)->MapDisplay->map;
	tmp = (*data)->MapDisplay->map;
	while (tmp)
	{
		tmp_str1 =(char *)tmp->content;
		tmp_str2 = (char *)previous->content;
		while (tmp_str1[i])
		{
			if((tmp_str1[i] == '0' && (  ft_strlen(tmp_str2) - 2 < i || tmp_str2[i] == ' '))\
				|| check_previous(tmp_str2,ft_strlen(tmp_str1)))
				return -1;
			i++;
		}
		i = 0;
		previous = tmp;
		tmp = tmp->next;
	}
	return 0;
}

static int parseMap(char *line, t_data **Data, int fd)
{
	int i;

	i = 0;
	i = skip_space(line);
	while(line && line[i])
	{
		i = skip_space(line);
		if(ft_strlen(line) > (*Data)->MapDisplay->NbrOfColumns)
			(*Data)->MapDisplay->NbrOfColumns = ft_strlen(line);
		ft_lstadd_back(&(*Data)->MapDisplay->map, ft_lstnew(line));
		(*Data)->MapDisplay->NbrOfRows++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if(check_line_is_valid(Data) == -1)
		ErrorMessage("Invalid map");
	// isMapValid(&(*Data)->MapDisplay->map);
	//need to implement is map valid function
	return(0);
}

int parseColors(char *line, t_colors **colors)
{
	char **RGB;
	int i;
	int product;
	
	i = 0;
	while(ft_isspace(line[i]))
		i++;
	line[ft_strlen(line)-1] = 0;
	RGB = ft_split(&line[i], ',');
	(*colors)->R = ft_atoi(RGB[0]);
	(*colors)->G = ft_atoi(RGB[1]);
	(*colors)->B = ft_atoi(RGB[2]);
	freeArray(RGB);
	product = (*colors)->R * (*colors)->G * (*colors)->B;
	if((*colors)->R > 255 || (*colors)->G > 255 || (*colors)->B > 255 || product < 0)
		ErrorMessage("Invalid colors");
	return(1);
}

static int parseLine(char *line, t_data **Data, int fd)
{
	int i;

	i = 0;
	while(ft_isspace(line[i]))
		i++;
	if(line[i]){
		if(!ft_strncmp(&line[i], "NO ", 3))
			return(parseTexture(&line[i+2], &(*Data)->MapDisplay->textures->North));
		else if(!ft_strncmp(&line[i], "SO  ", 3))
			return(parseTexture(&line[i+2], &(*Data)->MapDisplay->textures->South));
		else if(!ft_strncmp(&line[i], "WE ", 3))
			return(parseTexture(&line[i+2], &(*Data)->MapDisplay->textures->West));
		else if(!ft_strncmp(&line[i], "EA ", 3))
			return(parseTexture(&line[i+2], &(*Data)->MapDisplay->textures->East));
		else if(!ft_strncmp(&line[i], "F ", 2))
			return(parseColors(&line[i+1], &(*Data)->MapDisplay->FloorColor));
		else if(!ft_strncmp(&line[i], "C ", 2))
			return(parseColors(&line[i+1], &(*Data)->MapDisplay->CeilingColor));
		else if(line[i] == '1')
			return(parseMap(line, Data, fd));
		else
			ErrorMessage("Invalid map.");
	}
	return(1);
}


void Parser(char *MapPath, t_data **Data)
{
	int fd;
	(void)Data;

	fd = open_file(MapPath);
	char *tmp;
	tmp = get_next_line(fd);
	while(tmp)
	{
		if(!parseLine(tmp, Data, fd))
			break;
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
}
