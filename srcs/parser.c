/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:26 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/16 11:46:42 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_map(char *line, t_data **Data, int fd)
{
	int		i;
	char	*one_line_map;

	one_line_map = ft_strdup("\0");
	i = skip_space(line);
	while (line && line[i] && line[i] == '1')
	{
		i = 0;
		if (ft_strlen(line) > (*Data)->mapdisplay->columns_nbr)
			(*Data)->mapdisplay->columns_nbr = ft_strlen(line);
		one_line_map = ft_strjoin(one_line_map, line);
		one_line_map = ft_strjoin(one_line_map, ",");
		free(line);
		line = get_next_line(fd);
		(*Data)->mapdisplay->rows_nbr++;
		i = skip_space(line);
		if (line && line[i] && line[i] != '1')
			error_message("Invalid map");
	}
	free(line);
	(*Data)->mapdisplay->map = ft_split(one_line_map, ',');
	free(one_line_map);
	check_map_is_valid(Data);
	return (0);
}



static int	parse_line(char *line, t_data **Data, t_map **Map, int fd)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if(!ft_strncmp(&line[i], "NO ", 3)||!ft_strncmp(&line[i], "SO ", 3)\
		||!ft_strncmp(&line[i], "WE ", 3)||!ft_strncmp(&line[i], "EA ", 3))
		parse_textures(line,Data,Map);
		else if (!ft_strncmp(&line[i], "C ", 2))
		parse_colors(&line[i + 1],&(*Map)->ceiling_color);
	else if (!ft_strncmp(&line[i], "F ", 2))
		parse_colors(&line[i + 1], &(*Map)->floor_color);
	else if (line[i])
	{
		if (line[i] == '1')
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

	fd = check_file(MapPath);
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (!parse_line(tmp, Data, &(*Data)->mapdisplay, fd))
			break ;
		free(tmp);
		tmp = get_next_line(fd);
	}
	if(!tmp && (*Data)->mapdisplay->rows_nbr == 0)
		error_message("Invalid map 5");
	close(fd);
}
