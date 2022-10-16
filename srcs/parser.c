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

static int parseMap(char *line, t_data **Data, int fd)
{
	int i;

	i = 0;
	i = skip_space(line);
	while(line && line[i] == '1')
	{
		if(ft_strlen(line) > (*Data)->MapDisplay->NbrOfColumns)
			(*Data)->MapDisplay->NbrOfColumns = ft_strlen(line);
		ft_lstadd_back(&(*Data)->MapDisplay->map, ft_lstnew(line));
		(*Data)->MapDisplay->NbrOfRows++;
		free(line);
		line = get_next_line(fd);
		i = skip_space(line);
		if(line[i] == '0')
			ErrorMessage("Invalid map.");
	}
	free(line);
	check_map_is_valid(Data);
	return(0);
}

int parseColors(char *line, t_colors **colors)
{
	char **RGB;
	int i;

	
	i = 0;
	while(ft_isspace(line[i]))
		i++;
	line[ft_strlen(line)-1] = 0;
	RGB = ft_split(&line[i], ',');
	(*colors)->R = ft_atoi(RGB[0]);
	(*colors)->G = ft_atoi(RGB[1]);
	(*colors)->B = ft_atoi(RGB[2]);
	freeArray(RGB);
	if((*colors)->R > 255 || (*colors)->G > 255 || (*colors)->B > 255 
		|| (*colors)->R < 0 || (*colors)->G < 0 || (*colors)->B < 0)
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
			ErrorMessage("Invalid map 4");
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
