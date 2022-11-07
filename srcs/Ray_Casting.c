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
    
    grid_index_y = (int)(y / MINIMAP_TILE_SIZE);
    if(grid_index_y >= data->MapDisplay->NbrOfRows || grid_index_y < 0)
        return (false);
    grid_index_x = (int)(x / MINIMAP_TILE_SIZE);
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
	horz->yintercept = ((int)((data->player->y / MINIMAP_TILE_SIZE)) * MINIMAP_TILE_SIZE);
    if (ray->if_down)
        horz->yintercept += MINIMAP_TILE_SIZE;
    horz->xintercept = (data->player->x + (horz->yintercept - data->player->y) / tan(ray->ray_angle));
    horz->h_ystep = MINIMAP_TILE_SIZE;
    if (ray->if_up)
        horz->h_ystep *= -1;
    horz->h_xstep = MINIMAP_TILE_SIZE / tan(ray->ray_angle);
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
    while (horz->xintercept >= 0 && horz->xintercept <= (data->MapDisplay->NbrOfColumns * MINIMAP_TILE_SIZE) && horz->yintercept >= 0 && horz->yintercept <= (data->MapDisplay->NbrOfRows * MINIMAP_TILE_SIZE))
    {
        if (has_wall_at(horz->xintercept, horz->yintercept, data))
        {
            horz->found_horz_wallhit = true;
            ray->wallhit_x = horz->xintercept;
            ray->wallhit_y = horz->yintercept;
            horz->horz_distance = hypotf(data->player->x - ray->wallhit_x, data->player->y - ray->wallhit_y);
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
	vert->xintercept = ((int) ((data->player->x / MINIMAP_TILE_SIZE)) * MINIMAP_TILE_SIZE);
    if (ray->if_R)
        vert->xintercept += MINIMAP_TILE_SIZE;
    vert->yintercept = (data->player->y + (vert->xintercept - data->player->x ) * tan(ray->ray_angle));
    vert->v_xstep = MINIMAP_TILE_SIZE;
    if (ray->if_L)
        vert->v_xstep *= -1;
    vert->v_ystep = MINIMAP_TILE_SIZE * tan(ray->ray_angle);
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
    while (vert->xintercept >= 0 && vert->xintercept <= (data->MapDisplay->NbrOfColumns * MINIMAP_TILE_SIZE) && vert->yintercept >= 0 && vert->yintercept <= (data->MapDisplay->NbrOfRows * MINIMAP_TILE_SIZE))
    {
        if (has_wall_at(vert->xintercept, vert->yintercept, data))
        {
            vert->found_vert_wallhit = true;
            ray->wallhit_x = vert->xintercept;
            ray->wallhit_y = vert->yintercept;
            vert->vert_distance = hypotf(data->player->x - ray->wallhit_x, data->player->y - ray->wallhit_y);
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

float intercept(t_ray *rays, t_data *data)
{
    t_distance *distance;

	distance = NULL;
	distance = init_t_distance();
	distance = horz_distance(rays, data, distance);
	distance = vert_distance(rays, data, distance);
    if (distance->vert_distance < distance->horz_distance)
        return(distance->vert_distance);
    return(distance->horz_distance);
}


void draw_rectangle(t_data **data, int x, int y, float length)
{
	int i;
	int j;
	int tmp_x;
	unsigned long color;

	i = -1;
	tmp_x = x;
	color = 0xbf0001;
	if(length >= WINDOW_HEIGHT)
	{
		length = WINDOW_HEIGHT;
		y = 0;
	}
	while(++i < length)
	{
		x = tmp_x;
		j = -1;
		while(++j <  RAY_STRIP_WIDTH)
		{
			my_mlx_pixel_put((*data)->img, x+j, y+i, color);
		}
	}
}

void    cast_rays(t_data *data)
{
    int columnID = 0;
    int i = 0;
    float ray_angle;
    t_ray *ray;
	float wall_strip_height;
	float ray_length;
	float distance_projection_plane = (WINDOW_WIDTH/2) * tan(50*DEGREE);
    
    ray_angle = data->player->initialAngle - (FOV/2);
    // ray_angle = data->player->initialAngle;
    while (i < WINDOW_WIDTH)
	{
    
		ray = init_t_ray(ray_angle);
		ray->distance = intercept(ray,data);
		ray_length = ray->distance * cos(fabsf(ray_angle - data->player->initialAngle));
		wall_strip_height = ((TILE_SIZE / (ray_length * 10)) * distance_projection_plane);
		draw_rectangle(&data, i*RAY_STRIP_WIDTH, (WINDOW_HEIGHT/2) - (wall_strip_height/2), wall_strip_height);
        // drawline(&data, cos(ray_angle) * ray->distance , sin(ray_angle) * ray->distance);
        ray_angle += (FOV / WINDOW_WIDTH);
        columnID++;
        i++;
    }
	draw_minimap(&data);
}