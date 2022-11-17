/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:15:49 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/11/17 01:00:36 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include<stdio.h>
# include<stdlib.h>
# include<errno.h>
# include<fcntl.h>
# include<string.h>
# include<stdbool.h>
# include<unistd.h>
# include<mlx.h>
# include <math.h>

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900
# define PI 3.14159265
# define DEGREE 0.0174532925
# define MINIMAP_COEFF 8
# define TILE_SIZE 64
# define RADIUS 3
# define NORTH 1.5708
# define EAST 0
# define SOUTH 4.71239
# define WEST 3.14159
# define LINE_LENGTH 60
# define FOV 1.0472
# define S_KEY 1
# define A_KEY 2
# define W_KEY 13
# define D_KEY 0
# define RIGHT_ARROW 123
# define LEFT_ARROW 124
# define UP_ARROW 126
# define DOWN_ARROW 125
// # define WINDOW_WIDTH 3200
// # define WINDOW_HEIGHT 2000
// # define WINDOW_WIDTH 960
// # define WINDOW_HEIGHT 600

typedef struct s_horz
{
	float	xintercept;
	float	yintercept;
	float	h_xstep;
	float	h_ystep;
	float	horz_distance;
	bool	found_horz_wallhit;
}	t_horz;

typedef struct s_vert
{
	float	xintercept;
	float	yintercept;
	float	v_xstep;
	float	v_ystep;
	float	vert_distance;
	bool	found_vert_wallhit;
}	t_vert;

typedef struct s_distance
{
	float	vert_distance;
	float	horz_distance;
}t_distance;

typedef struct s_ray
{
	float	ray_angle;
	float	v_wallhit_x;
	float	v_wallhit_y;
	float	h_wallhit_x;
	float	h_wallhit_y;
	float	distance;
	bool	if_down;
	bool	if_up;
	bool	if_r;
	bool	if_l;
	bool	is_vert;
	bool	is_horz;
}t_ray;
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_img;

typedef struct s_win {
	void	*mlx_win;
	t_img	*win_img;
	int		columns;
	int		lines;
}t_win;

typedef struct s_colors{
	int		r;
	int		g;
	int		b;
	bool	flag;
}t_colors;

typedef struct s_text_path{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}t_text_path;

typedef struct s_text_img{
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
}t_text_img;

typedef struct s_map{
	char		**map;
	int			rows_nbr;
	int			columns_nbr;
	t_text_path	*text_paths;
	t_colors	*floor_color;
	t_colors	*ceiling_color;
	t_text_img	*text_imgs;
	t_img		*wall;
	t_img		*wall_2;
	t_ray		*ray;
}t_map;

typedef struct s_player{
	float	x;
	float	y;
	float	turn_direction;
	int		walk_direction;
	float	side_angle;
	float	initial_angle;
	float	move_speed;
	float	rotation_speed;
}t_player;

typedef struct s_data{
	t_map		*mapdisplay;
	t_win		*win;
	t_player	*player;
	void		*mlx_ptr;
}t_data;

void			error_message(char *message);
char			*ft_strchr(const char *s, int c);
void			Parser(char *MapPath, t_data **Data);
char			*get_next_line(int fd);
void			constructor(t_data **Data);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strlen(char *str);
char			**ft_split(char const *s, char c);
void			free_array(char **arr);
bool			ft_isspace(char c);
char			*ft_substr(char *s, int start, int len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(char *s1);
int				ft_atoi(const char *str);
int				ft_strisdigit(char *str);
int				check_map_is_valid(t_data **data, char *curr_l, char *prev_l);
int				skip_space(char *str);
void			draw_map(t_data **Data);
int				close_win(t_data *Data);
int				key_press(int keycode, t_data **data);
void			draw_minimap(t_data **Data);
int				keyrelease(int keycode, t_data **data);
int				handler(t_data **data);
void			checkWallCollision(t_data **data);
int				is_valid_char(char c);
unsigned int	create_rgb(int r, int g, int b);
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
void			draw_square(t_data **data, int x, int y, unsigned long color);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				check_file(char *MapPath);
void			parser(char *MapPath, t_data **Data);
void			cast_rays(t_data *data);
void			drawline(t_data **data, float dx, float dy);
void			init_game_loop(t_data **data);
void			draw_in_window(t_data **data);
void			draw_background(t_data **data);
void			move_player(t_data **data, t_player **player);
void			draw_player(t_data **data);
void			intercept(t_data *data);
unsigned int	my_mlx_pixel_get(t_img *img, int x, int y);
void			*create_img(t_data *data, char *path);
bool			parse_textures(char *line, t_data **data, t_map **map);
int				parse_colors(char *line, t_colors **colors);
void			ft_putstr_fd(char *s, int fd);
float			normalize_angle(float angle);
void			init_t_ray(t_ray **ray, float ray_angle);
void			render_wall(t_data *data, int x, t_ray *ray, int dtpp);
bool			ft_isspace(char c);
int				button_release(int button_code, int x, int y, t_data **data);
int				button_press(int button_code, int x, int y, t_data **data);
bool			has_wall_at(float x, float y, t_data *data);
t_horz			*init_t_horz(void);
void			calculate_horz_step(t_horz *horz, t_data *data, t_ray *ray);
void			h_wall_hit(t_horz *horz, t_data *data, t_ray *ray);
t_distance		*horz_distance(t_ray *ray, t_data *data, t_distance *distance);
t_vert			*init_t_vert(void);
void			calculate_ver_step(t_vert *vert, t_data *data, t_ray *ray);
int				size_2d_array(char **arr);

#endif
