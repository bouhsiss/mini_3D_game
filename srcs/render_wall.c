#include "cub3D.h"


int adjust_length(int wall_strip_height, int *end)
{
	int start;

	start = (WINDOW_HEIGHT/2) - (wall_strip_height/2);
	if(start < 0)
		start = 0;
	*end = (WINDOW_HEIGHT/2) + (wall_strip_height/2);
	if(*end > WINDOW_HEIGHT)
		*end = WINDOW_HEIGHT;
	return(start);
}


void *create_img(t_data *data,char *path)
{
	int x;
	int y;
	int fd;
	void *img_ptr;

	if(open(path, O_DIRECTORY) > 0)
		error_message("map should be a file not a directory.");
	fd = open(path, O_RDONLY);
	if(fd == -1)
	{
		error_message(strerror(errno));
	}
	img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, &x, &y);
	if(img_ptr == NULL)
		error_message("xpm file not valid.");
	return(img_ptr);
}

t_img *north_or_south(t_data *data, float ray_angle)
{
	if(ray_angle >= 0 && ray_angle <= PI)
		return(data->MapDisplay->text_imgs->North);
	else
		return(data->MapDisplay->text_imgs->South);
}

t_img *east_or_west(t_data *data, float ray_angle)
{
	if(ray_angle >= PI/2 && ray_angle <= (3*PI)/2)
		return(data->MapDisplay->text_imgs->West);
	else
		return(data->MapDisplay->text_imgs->East);
}

void map_texture_to_wall(t_data *data, int x, int y, t_ray *ray, int offset_y, float ray_angle)
{
	int offset_x;
	t_img *texture;
	unsigned int color;

	ray_angle = fmod(2*PI  + fmod(ray_angle, 2*PI), 2*PI);
	if(ray->is_vert == true)
	{
		offset_x = (int)ray->v_wallhit_y % TILE_SIZE;
		texture = east_or_west(data, ray_angle);
		color = my_mlx_pixel_get(texture, offset_x, offset_y);
	}
	else
	{
		offset_x = (int)ray->h_wallhit_x % TILE_SIZE;
		texture = north_or_south(data, ray_angle);
		color = my_mlx_pixel_get(texture, offset_x, offset_y);
	}
	my_mlx_pixel_put(data->win->win_img, x, y, color);
}



void render_wall(t_data *data, float ray_length, float ray_angle, int x, t_ray *ray, float distance_projection_plane)
{
	int wall_strip_height;
	int y;
	int end;

	ray_length = ray_length * cos(ray_angle - data->player->initialAngle);
	wall_strip_height = (TILE_SIZE/(ray_length) * distance_projection_plane);
	y = adjust_length(wall_strip_height, &end);
	while(y < end)
	{
		int offset_y = (y + (wall_strip_height / 2) - 0.5 * WINDOW_HEIGHT)
			* ((float)TILE_SIZE / wall_strip_height);
		map_texture_to_wall(data, x, y, ray, offset_y, ray_angle);
		y++;
	}
}

