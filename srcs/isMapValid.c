/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isMapValid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:31:02 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/17 01:08:37 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_first_and_last_line(char *line, int flag)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (is_valid_char(line[i]))
			return (1);
	}
	if (flag == 1 && line[ft_strlen(line) - 1] == '\n')
		error_message("Invalid map");
	return (0);
}

int	check_two_line(char *curr_line, char *prev_line, int i)
{
	if ((ft_isspace(curr_line[i]) && is_valid_char(curr_line[i - 1])) \
	|| ((is_valid_char(curr_line[i]) && (ft_isspace(curr_line[i - 1]) \
	|| ft_strlen(prev_line) - 1 < i || ft_isspace(prev_line[i])))))
		error_message("Invalid map");
	else if (ft_strlen(prev_line) - 2 > i && (((is_valid_char(prev_line[i]) \
	&& (ft_isspace(prev_line[i - 1]) || ft_strlen(curr_line) - 1 < i \
	|| ft_isspace(curr_line[i]))))))
		error_message("Invalid map");
	else if (!is_valid_char(curr_line[i]) && curr_line[i] \
	!= '1' && !ft_isspace(curr_line[i]))
		error_message("Invalid map");
	return (0);
}

int	saveplayerpos(int i, int j, t_data **data, char c)
{
	(*data)->player->x = i * TILE_SIZE + (TILE_SIZE / 2);
	(*data)->player->y = j * TILE_SIZE + (TILE_SIZE / 2);
	if (c == 'N')
		(*data)->player->initial_angle = NORTH ;
	if (c == 'S')
		(*data)->player->initial_angle = SOUTH ;
	if (c == 'E')
		(*data)->player->initial_angle = EAST ;
	if (c == 'W')
		(*data)->player->initial_angle = WEST ;
	return (1);
}

int	check_line(t_data **data, char *curr_line, char *prev_line, int curr)
{
	int	i;
	int	flag;

	flag = 0;
	i = ft_strlen(curr_line) - 1;
	while (i)
	{
		if (curr_line[i] == 'N' || curr_line[i] == 'S' \
		|| curr_line[i] == 'E' || curr_line[i] == 'W')
			flag += saveplayerpos(i, curr, data, curr_line[i]);
		if (check_two_line(curr_line, prev_line, i) || flag > 1)
			error_message("Invalid map");
		i--;
	}
	return (flag);
}

int	check_map_is_valid(t_data **data, char *curr_line, char *prev_line)
{
	int		curr;
	int		prev;
	int		flag;

	flag = 0;
	curr = 0;
	prev = 0;
	if (check_first_and_last_line((*data)->mapdisplay->map[prev], 0))
		error_message("Invalid map");
	while ((*data)->mapdisplay->map[curr])
	{
		curr_line = (*data)->mapdisplay->map[curr];
		prev_line = (*data)->mapdisplay->map[prev];
		flag += check_line(data, curr_line, prev_line, curr);
		prev = curr;
		curr++;
	}
	if (check_first_and_last_line(curr_line, 1) || flag == 0)
		error_message("Invalid map");
	return (0);
}
