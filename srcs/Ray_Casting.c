/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray_Casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:23:49 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/06 22:36:52 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	has_wall_at(float x,float y,t_data *data)
{
    int grid_index_x;
    int grid_index_y;
    
    grid_index_y = (int)(y / TILE_SIZE);
    if(grid_index_y >= data->MapDisplay->NbrOfRows || grid_index_y < 0)
        return (false);
    grid_index_x = (int)(x / TILE_SIZE);
    if(grid_index_x > ft_strlen(data->MapDisplay->map[grid_index_y]) - 1 || grid_index_x < 0)
        return (false);
    return (!is_valid_char(data->MapDisplay->map[grid_index_y][grid_index_x]));
}

t_horz	*init_t_horz(void)
{
	t_horz *horz;
	
	horz = malloc(sizeof(t_horz));
	horz->xintercept = 0;
	horz->yintercept = 0;
	horz->h_xstep = 0;
	horz->h_ystep = 0;
	horz->horz_distance = 0;
	horz->found_horz_wallhit = false;
	return (horz);
}

void	calculate_horz_step(t_horz *horz, t_data *data, t_ray *ray)
{
	horz->yintercept = ((int)((data->player->y / TILE_SIZE))) * TILE_SIZE;
    if (ray->if_down)
        horz->yintercept += TILE_SIZE;
    horz->xintercept = (data->player->x + (horz->yintercept - data->player->y) / tan(ray->ray_angle));
    horz->h_ystep = TILE_SIZE;
    if (ray->if_up)
        horz->h_ystep *= -1;
    horz->h_xstep = TILE_SIZE / tan(ray->ray_angle);
    if (ray->if_L && horz->h_xstep > 0)
        horz->h_xstep *= -1;
    if (ray->if_R && horz->h_xstep < 0)
        horz->h_xstep *= -1;
    if(ray->if_up)
        horz->yintercept--;
}

t_distance	*horz_distance(t_ray *ray,t_data *data,t_distance *distance)
{
	t_horz	*horz;
	
	horz = init_t_horz();
	calculate_horz_step(horz, data, ray);
    while (horz->xintercept >= 0 && horz->xintercept <= (data->MapDisplay->NbrOfColumns * TILE_SIZE) && horz->yintercept >= 0 && horz->yintercept <= (data->MapDisplay->NbrOfRows * TILE_SIZE))
    {
        if (has_wall_at(horz->xintercept, horz->yintercept, data))
        {
            horz->found_horz_wallhit = true;
            ray->h_wallhit_x = horz->xintercept;
            ray->h_wallhit_y = horz->yintercept;
			if(ray->if_up)
				ray->h_wallhit_y++;
            horz->horz_distance = hypotf(ray->h_wallhit_x - data->player->x, ray->h_wallhit_y - data->player->y );
            break;
        }
        else
        {
            horz->xintercept += horz->h_xstep;
            horz->yintercept += horz->h_ystep;
        }
    }
	if(horz->found_horz_wallhit)
		distance->horz_distance = horz->horz_distance;
	free(horz);
	return (distance);
}

t_vert	*init_t_vert(void)
{
	t_vert *vert;
	
	vert = malloc(sizeof(t_vert));
	vert->xintercept = 0;
	vert->yintercept = 0;
	vert->v_xstep = 0;
	vert->v_ystep = 0;
	vert->vert_distance = 0;
	vert->found_vert_wallhit = false;
	return (vert);
}

void	calculate_ver_step(t_vert *vert, t_data *data, t_ray *ray)
{
	vert->xintercept = ((int) ((data->player->x / TILE_SIZE))) * TILE_SIZE;
    if (ray->if_R)
        vert->xintercept += TILE_SIZE;
    vert->yintercept = (data->player->y + (vert->xintercept - data->player->x ) * tan(ray->ray_angle));
    vert->v_xstep = TILE_SIZE;
    if (ray->if_L)
        vert->v_xstep *= -1;
    vert->v_ystep = TILE_SIZE * tan(ray->ray_angle);
    if (ray->if_up && vert->v_ystep > 0)
        vert->v_ystep *= -1;
    if (ray->if_down && vert->v_ystep < 0)
        vert->v_ystep *= -1;
    if(ray->if_L)
        vert->xintercept--;
}

t_distance	*vert_distance(t_ray *ray,t_data *data,t_distance *distance)
{
	t_vert	*vert;

	vert = init_t_vert();
	calculate_ver_step(vert, data, ray);
    while (vert->xintercept >= 0 && vert->xintercept <= (data->MapDisplay->NbrOfColumns * TILE_SIZE) && vert->yintercept >= 0 && vert->yintercept <= (data->MapDisplay->NbrOfRows * TILE_SIZE))
    {
        if (has_wall_at(vert->xintercept, vert->yintercept, data))
        {
            vert->found_vert_wallhit = true;
            ray->v_wallhit_x = vert->xintercept;
            ray->v_wallhit_y = vert->yintercept;
			if(ray->if_L)
				ray->v_wallhit_x++;
            vert->vert_distance = hypotf( ray->v_wallhit_x - data->player->x, ray->v_wallhit_y - data->player->y);
            break;
        }
        else
        {
            vert->xintercept += vert->v_xstep;
            vert->yintercept += vert->v_ystep;
        }
    }
	if(vert->found_vert_wallhit)
		distance->vert_distance = vert->vert_distance;
	free(vert);
	return (distance);
}

t_distance	*init_t_distance(void)
{
	t_distance *distance;
	
	distance = malloc(sizeof(t_distance));
	distance->horz_distance = INT64_MAX;
	distance->vert_distance = INT64_MAX;
	return (distance);
}

void intercept(t_data *data)
{
    t_distance *distance;

	distance = NULL;
	distance = init_t_distance();
	distance = horz_distance(data->MapDisplay->ray, data, distance);
	distance = vert_distance(data->MapDisplay->ray, data, distance);
	if (distance->vert_distance < distance->horz_distance)
	{
		data->MapDisplay->ray->distance = distance->vert_distance;
		data->MapDisplay->ray->is_vert = true;
	}
    else
	{
		data->MapDisplay->ray->distance = distance->horz_distance;
		data->MapDisplay->ray->is_horz = true;
	}
	free(distance);
}


void    cast_rays(t_data *data)
{
    int i = -1;
    float ray_angle;
	float distance_projection_plane = ((WINDOW_WIDTH/2) / tan(FOV/2));
    
    while (++i < WINDOW_WIDTH)
	{
		ray_angle = data->player->initialAngle + atan((i - 0.5 * WINDOW_WIDTH) / distance_projection_plane);
		init_t_ray(&data->MapDisplay->ray, ray_angle);
		intercept(data);
		render_wall(data, data->MapDisplay->ray->distance, ray_angle, i, data->MapDisplay->ray, distance_projection_plane);
    }
	draw_minimap(&data);
}