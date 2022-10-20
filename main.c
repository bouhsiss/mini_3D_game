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
		Parser(av[1], &data);
		draw_map(&data);
		ft_lstdelete(&data->MapDisplay->map);
		// system("Leaks cub3D");
	}
	else
		ErrorMessage("Usage : ./cub3D < .cub map file >");
}
