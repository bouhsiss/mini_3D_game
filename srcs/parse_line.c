/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:27:57 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/16 17:21:36 by omeslall         ###   ########.fr       */
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
    if (!ft_strncmp(&line[i], "NO ", 3) && !(*data)->mapdisplay->text_paths->north)
		return (parse_texture(&line[i + 2], &(*map)->text_paths->north));
	else if (!ft_strncmp(&line[i], "SO  ", 3)&& !(*data)->mapdisplay->text_paths->south)
		return (parse_texture(&line[i + 2], &(*map)->text_paths->south));
	else if (!ft_strncmp(&line[i], "WE ", 3)&& !(*data)->mapdisplay->text_paths->west)
		return (parse_texture(&line[i + 2], &(*map)->text_paths->west));
	else if (!ft_strncmp(&line[i], "EA ", 3)&& !(*data)->mapdisplay->text_paths->east)
		return (parse_texture(&line[i + 2], &(*map)->text_paths->east));
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
        if(ft_isspace(line[i]) && comma == 2)
        {
            i += (size_t)skip_space(&line[i]);
            if(line[i])
                error_message("=>Invalid colors");
        }
        
        if(i && ft_isspace(line[i])&& comma != 2){
            printf("line[%zu] = %d\n",i,line[i]);
            error_message("==>Invalid colors");
        }
        i++;
    }
    if(line[i] == ',')
    {
        comma++;
        i++;
    }
    if((line[i] < 48 || line[i] > 57 || comma > 2) && line[i])
    {
        printf("=>line[%zu] = %d\n",i,line[i]);
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
    check_line_color(&line[i]);
	rgb = ft_split(&line[i], ',');
	if (size_2d_array(rgb) != 3)
		error_message("Invalid colors");
	(*colors)->r = ft_atoi(rgb[0]);
	(*colors)->g = ft_atoi(rgb[1]);
	(*colors)->b = ft_atoi(rgb[2]);
	free_array(rgb);
	if ((*colors)->r > 255 || (*colors)->g > 255 || (*colors)->b > 255 \
		|| (*colors)->r < 0 || (*colors)->g < 0 || (*colors)->b < 0)
		error_message("Invalid colors");
    // exit(0);
	return (1);
}