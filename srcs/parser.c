/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:26 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/21 14:20:14 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_texture(char *line, char **Data)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	(*Data) = ft_substr(line, i, ft_strlen(line) - i + 1);
	return (1);
}

static int	parse_map(char *line, t_data **Data, int fd)
{
	int		i;
	char	*one_line_map;

	one_line_map = ft_strdup("\0");
	i = skip_space(line);
	while (line && line[i] && line[i] == '1')
	{
		i = 0;
		if (ft_strlen(line) > (*Data)->MapDisplay->NbrOfColumns)
			(*Data)->MapDisplay->NbrOfColumns = ft_strlen(line);
		one_line_map = ft_strjoin(one_line_map, line);
		one_line_map = ft_strjoin(one_line_map, ",");
		free(line);
		line = get_next_line(fd);
		(*Data)->MapDisplay->NbrOfRows++;
		i = skip_space(line);
		if (line && line[i] && line[i] != '1')
			error_message("Invalid map");
	}
	free(line);
	(*Data)->MapDisplay->map = ft_split(one_line_map, ',');
	free(one_line_map);
	// int j = 0;
	// while((*Data)->MapDisplay->map[j])
	// {
	// 	printf("%s\n", (*Data)->MapDisplay->map[j]);
	// 	j++;
	// }
	check_map_is_valid(Data);
	return (0);
}

int	parse_colors(char *line, t_colors **colors)
{
	char	**rgb;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	line[ft_strlen(line)-1] = 0;
	rgb = ft_split(&line[i], ',');
	if (rgb[3])
		error_message("Invalid colors");
	(*colors)->R = ft_atoi(rgb[0]);
	(*colors)->G = ft_atoi(rgb[1]);
	(*colors)->B = ft_atoi(rgb[2]);
	free_array(rgb);
	if ((*colors)->R > 255 || (*colors)->G > 255 || (*colors)->B > 255 \
		|| (*colors)->R < 0 || (*colors)->G < 0 || (*colors)->B < 0)
		error_message("Invalid colors");
	return (1);
}

static int	parse_line(char *line, t_data **Data, t_map **Map, int fd)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i])
	{
		if (!ft_strncmp(&line[i], "NO ", 3))
			return (parse_texture(&line[i + 2], &(*Map)->textures->North));
		else if (!ft_strncmp(&line[i], "SO  ", 3))
			return (parse_texture(&line[i + 2], &(*Map)->textures->South));
		else if (!ft_strncmp(&line[i], "WE ", 3))
			return (parse_texture(&line[i + 2], &(*Map)->textures->West));
		else if (!ft_strncmp(&line[i], "EA ", 3))
			return (parse_texture(&line[i + 2], &(*Map)->textures->East));
		else if (!ft_strncmp(&line[i], "F ", 2))
			return (parse_colors(&line[i + 1], &(*Map)->FloorColor));
		else if (!ft_strncmp(&line[i], "C ", 2))
			return (parse_colors(&line[i + 1], &(*Map)->CeilingColor));
		else if (line[i] == '1')
			return (parse_map(line, Data, fd));
		else
			error_message("Invalid map 4");
	}
	return (1);
}

void	parser(char *MapPath, t_data **Data)
{
	int		fd;
	char	*tmp;

	fd = open_file(MapPath);
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (!parse_line(tmp, Data, &(*Data)->MapDisplay, fd))
			break ;
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
}
