/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:03:37 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/10/19 11:03:39 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error_message(char *message)
{
	printf("Error : \n");
	printf("%s", message);
	printf("\n");
	exit(EXIT_FAILURE);
}
