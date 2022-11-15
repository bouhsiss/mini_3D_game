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
	horz->yintercept = ((int)((data->player->y / TILE_SIZE)) * TILE_SIZE);
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
            ray->wallhit_x = horz->xintercept;
            ray->wallhit_y = horz->yintercept;
			if(ray->if_up)
				ray->wallhit_y++;
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
	vert->xintercept = ((int) ((data->player->x / TILE_SIZE)) * TILE_SIZE);
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
            ray->wallhit_x = vert->xintercept;
            ray->wallhit_y = vert->yintercept;
			if(ray->if_L)
				ray->wallhit_x++;
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
		data->MapDisplay->ray->distance = distance->vert_distance/3;
		// printf("ray %f\n", data->MapDisplay->ray->distance);
		data->MapDisplay->ray->is_vert = true;
	}
    else
	{
		data->MapDisplay->ray->distance = distance->horz_distance/3;
		// printf("ray %f\n", data->MapDisplay->ray->distance);
		data->MapDisplay->ray->is_horz = true;
	}
	free(distance);
}

int adjust_length(int *wall_strip_height)
{
	int start;
	int end;

	start = (WINDOW_HEIGHT/2) - (*wall_strip_height/2);
	if(start < 0)
		start = 0;
	end = (WINDOW_HEIGHT/2) + (*wall_strip_height/2);
	if(end > WINDOW_HEIGHT)
		end = WINDOW_HEIGHT;
	*wall_strip_height = end - start;
	return(start);
}

void *create_img(t_data *data,char *path)
{
	int x;
	int y;
	return(mlx_xpm_file_to_image(data->mlx_ptr, path, &x, &y));
}

void map_texture_to_wall(t_data *data, int x, int y, t_ray *ray, int offset_y, float ray_angle)
{
	int offset_x;
	(void)offset_y;
	unsigned int color = create_rgb(50, 0 , 0);
	if(ray->is_vert == true)
	{
		offset_x = (int)(fabs(ray->distance*sin(ray_angle))) % TILE_SIZE;
		color = my_mlx_pixel_get(data->MapDisplay->wall, offset_x, offset_y);
		// color = create_rgb(0,0,100);
	}
	else
	{
		offset_x = (int)(fabs(ray->distance*cos(ray_angle))) % TILE_SIZE;
		color = my_mlx_pixel_get(data->MapDisplay->wall_2, offset_x, offset_y);
	}
	my_mlx_pixel_put(data->img, x, y, color);
}

void render_wall(t_data *data, float ray_length, float ray_angle, int x, t_ray *ray)
{
	int wall_strip_height;
	float distance_projection_plane;
	int y;
	int i;

	i = -1;
	distance_projection_plane = (WINDOW_WIDTH/2) * tan(30*DEGREE); //461
	ray_length = (ray_length * cos(ray_angle - data->player->initialAngle));
	wall_strip_height = ((TILE_SIZE/(ray_length)) * distance_projection_plane);
	y = adjust_length(&wall_strip_height);
	// int offset_x;
	// if(ray->is_vert == true)
	// 	offset_x = (int)ray->wallhit_y % TILE_SIZE;
	// else
	// 	offset_x = (int)ray->wallhit_x % TILE_SIZE;
	while(++i < wall_strip_height)
	{
		map_texture_to_wall(data, x, y+i, ray, (i*((float)TILE_SIZE)/wall_strip_height), ray_angle);
	}
}

void    cast_rays(t_data *data)
{
    int columnID = 0;
    int i = -1;
    float ray_angle;
    
    ray_angle = data->player->initialAngle - (FOV/2);
    while (++i < WINDOW_WIDTH)
	{
		init_t_ray(&data->MapDisplay->ray, ray_angle);
		intercept(data);
		// drawline(&data, cos(ray_angle) * data->MapDisplay->ray->distance , sin(ray_angle) * data->MapDisplay->ray->distance);
		render_wall(data, data->MapDisplay->ray->distance, ray_angle, i, data->MapDisplay->ray);
        ray_angle += (FOV / WINDOW_WIDTH);
        columnID++;
    }
	draw_minimap(&data);
}