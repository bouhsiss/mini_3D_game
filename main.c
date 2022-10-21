/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:00:30 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:00:32 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		constructor(&data);
		parser(av[1], &data);
		draw_map(&data);
		free_array(data->MapDisplay->map);
	}
	else
		error_message("Usage : ./cub3D < .cub map file >");
}
