#include "cub3D.h"

void	render_map(t_data **data)
{
	int		num_rays;
	float	ray_angle;
	float wall_strip_height;
	float distance_projection_plane;
	float ray_length;
	int		i;

	i = 0;
	int j;
	num_rays = WINDOW_WIDTH/RAY_STRIP_WIDTH;
	ray_angle = fmod(2*PI  + fmod((*data)->player->initialAngle, 2*PI), 2*PI) - (HORZ_FOV / 2);
	distance_projection_plane = (WINDOW_WIDTH/2) * tan(HORZ_FOV/2);
	(*data)->num_rays = num_rays;
	draw_mini_map(data);
	while (i < num_rays)
	{
		j = 0;
		ray_angle = fmod(2*PI  + fmod(ray_angle, 2*PI), 2*PI);
		ray_length = (cast_a_one_single_lonely_ray(data, ray_angle));
		ray_length = (ray_length * TILE_SIZE)* cos(fabsf(ray_angle - (*data)->player->initialAngle));
		wall_strip_height = ((TILE_SIZE / (ray_length)) * distance_projection_plane);
		draw_rectangle(data, i*RAY_STRIP_WIDTH, (WINDOW_HEIGHT/2) - (wall_strip_height/2), wall_strip_height);
		ray_angle += HORZ_FOV / num_rays;
		i++;
	}
}
