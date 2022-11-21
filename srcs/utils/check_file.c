/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:34:01 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/21 11:34:04 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	open_map_file(char *path)
{
	int	fd;

	if (open(path, O_DIRECTORY) > 0)
		error_message("map should be a file not a directory.");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_message(strerror(errno));
	return (fd);
}

int	check_file(char *MapPath)
{
	char	*ext;
	int		i;

	i = 0;
	if (MapPath[0] == '.' && MapPath[1] == '/')
		i += 2;
	ext = ft_strchr(&MapPath[i], '.');
	if (!ext || ft_strncmp(ext, ".cub", 4))
		error_message("map should have .cub extension");
	return (open_map_file(MapPath));
}
