#include "cub3D.h"

int up_or_down(float angle, int *var_y)
{
	if(angle >= 0 && angle <= PI)
	{
		*var_y = 1;
		return(RESOLUTION);
	}
	else
	{
		*var_y = -1;
		return(-1);
	}
}

int right_or_left(float ray_angle, int *var_x)
{
	if(ray_angle > PI/2 && ray_angle < (3*PI)/2)
	{
		*var_x = -1;
		return(-1);
	}
	else
	{
		*var_x = 1;
		return(RESOLUTION);
	}
}

float find_h_intersection(t_data **data, float ray_angle)
{
	float inter_x;
	float inter_y;
	float delta_x;
	int i;
	int j;
	float delta_y;
	int var_y;

	inter_y = (*data)->player->y/RESOLUTION;
	inter_y = (int)inter_y * RESOLUTION + up_or_down(ray_angle, &var_y);
	inter_x = (*data)->player->x + (inter_y - (*data)->player->y)/tan(ray_angle);
	delta_y = var_y * RESOLUTION;
	delta_x = RESOLUTION/tan(ray_angle);
	i = abs((int)inter_y/RESOLUTION);
	j = abs((int)inter_x/RESOLUTION);
	while( i >= 0 && i < (*data)->MapDisplay->NbrOfRows && j >= 0 && j <= ft_strlen(((*data)->MapDisplay->map[i])))
	{
		if((*data)->MapDisplay->map[i][j] == '1')
		{
			return(fabs(inter_y - (*data)->player->y)/sin(ray_angle));
		}
		inter_x += (var_y) * delta_x;
		inter_y += delta_y;
		i = abs((int)inter_y/RESOLUTION);
		j = abs((int)inter_x/RESOLUTION);
	}
	return(fabs(inter_y - (*data)->player->y)/sin(ray_angle));
}

float find_v_intersection(t_data **data, float ray_angle)
{
	float inter_x;
	float inter_y;
	float delta_x;
	float delta_y;
	int i;
	int j;
	int var_x;

	inter_x = (*data)->player->x/RESOLUTION;
	inter_x = (int)inter_x*RESOLUTION + right_or_left(ray_angle, &var_x);
	inter_y = (*data)->player->y + ( inter_x - (*data)->player->x)*tan(ray_angle);
	delta_x = var_x * RESOLUTION;
	delta_y = var_x *  RESOLUTION * tan(ray_angle);
	i = abs((int)inter_y/RESOLUTION);
	j = abs((int)inter_x/RESOLUTION);
	while( i >= 0 && i < (*data)->MapDisplay->NbrOfRows && j >= 0 && j <= ft_strlen(((*data)->MapDisplay->map[i])))
	{
		if((*data)->MapDisplay->map[i][j] == '1')
		{
			return(fabs(inter_y - (*data)->player->y)/sin(ray_angle));
		}
		inter_x += delta_x;
		inter_y += delta_y;
		i = abs((int)(inter_y)/RESOLUTION);
		j = abs((int)(inter_x)/RESOLUTION);
	}
	return(fabs(inter_y - (*data)->player->y)/sin(ray_angle));
}

void cast_a_one_single_lonely_ray(t_data **data, float ray_angle)
{
	float h_intersection;
	float v_intersection;

	h_intersection = fabsf(find_h_intersection(data, ray_angle));
	v_intersection = fabsf(find_v_intersection(data, ray_angle));
	if(h_intersection <= v_intersection)
		drawline(data, cos(ray_angle)*h_intersection, sin(ray_angle)*h_intersection, 0xB7CFFF);
	else
		drawline(data, cos(ray_angle)*v_intersection, sin(ray_angle)*v_intersection, 0xB7CFFF);
}


float sanitize(float angle)
{
	angle = fmod(angle, (2*PI));
	if(angle < 0)
	{
		angle = angle + (2*PI);
	}
	return(angle);
}

void draw_fov(t_data **data, float line_length)
{
	int num_rays = ((*data)->MapDisplay->NbrOfColumns * RESOLUTION)/RAY_STRIP_WIDTH*10;
	float ray_angle = sanitize((*data)->player->initialAngle - (FOV/2));
	int i = 0;
	(void)line_length;

	while(i < num_rays)
	{
		cast_a_one_single_lonely_ray(data, ray_angle);
		ray_angle += FOV/num_rays;
		ray_angle = sanitize(ray_angle);
		i++;
	}
}