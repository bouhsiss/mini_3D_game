/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:27:57 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/16 11:46:06 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_texture(char *line, char **Data)
{
	int	start;
	int len = 0;

	start = skip_space(line);
	int i;
	i = start;
	while(line[i+1])
	{
		if(ft_isspace(line[i])  && line[i-1] != '\\')
			error_message("mutiple xpm files.");
		i++;
		len++;
	}
	(*Data) = ft_substr(line, start, len);
	return (1);
}

bool    parse_textures(char *line,t_data **data,t_map **map)
{
    int i;
    
    i = skip_space(line);
    if (!ft_strncmp(&line[i], "NO ", 3) && !(*data)->MapDisplay->text_paths->North)
		return (parse_texture(&line[i + 2], &(*map)->text_paths->North));
	else if (!ft_strncmp(&line[i], "SO  ", 3)&& !(*data)->MapDisplay->text_paths->South)
		return (parse_texture(&line[i + 2], &(*map)->text_paths->South));
	else if (!ft_strncmp(&line[i], "WE ", 3)&& !(*data)->MapDisplay->text_paths->West)
		return (parse_texture(&line[i + 2], &(*map)->text_paths->West));
	else if (!ft_strncmp(&line[i], "EA ", 3)&& !(*data)->MapDisplay->text_paths->East)
		return (parse_texture(&line[i + 2], &(*map)->text_paths->East));
	error_message("Invalid map 42");
    return(true);
}

void    check_line_color(char *line)
{
    static size_t i;
    static size_t comma;

    if(i >= (size_t)ft_strlen(line))
    {
        i = 0;
        comma = 0;
        return;
    }
    while ((line[i]>=48 && line[i] <= 57 ) || ft_isspace(line[i]))
    {
        if(i && ft_isspace(line[i])){
            printf("line[%zu] = %d\n",i,line[i]);
			printf("line %s\n", line);
            error_message("==>Invalid colors");
        }
        i++;
    }
    if(line[i] == ',')
    {
        comma++;
        i++;
        if((line[i] < 48 || line[i] > 57) || (comma > 3))
            error_message("===>Invalid colors");
    }
    check_line_color(line);
    return;
}

int size_2d_array(char **arr)
{
    int i;

    i = 0;
    if(!arr)
        return(0);
    while(arr[i])
        i++;
    return(i);
}

int	parse_colors(char *line, t_colors **colors)
{
	char	**rgb;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	line[ft_strlen(line)-1] = 0;
    // check_line_color(&line[i]);
	rgb = ft_split(&line[i], ',');
	if (size_2d_array(rgb) != 3)
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