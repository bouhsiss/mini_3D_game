/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:34:01 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/21 11:34:04 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	open_file(char *MapPath)
{
	int	fd;

	if (open(MapPath, O_DIRECTORY) > 0)
		error_message("map should be a file not a directory.");
	if (ft_strncmp(ft_strchr(MapPath, '.'), ".cub", 4))
		error_message("map should have .cub extension");
	fd = open(MapPath, O_RDONLY);
	if (fd == -1)
		error_message(strerror(errno));
	return (fd);
}
