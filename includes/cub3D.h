#ifndef CUB3D_H 
#define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

# define PI 3.14159265
# define DEGREE 3.14159265/180
# define MINIMAP_COEFF 8
# define TILE_SIZE 64
# define RADIUS 3
# define NORTH 90*DEGREE
# define EAST 0*DEGREE
# define SOUTH 270*DEGREE
# define WEST 180*DEGREE
# define LINE_LENGTH 60
# define FOV 60*DEGREE
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
 

typedef struct s_lst
{
	void *content;
	struct s_lst *next;
	struct s_lst *previous;
}t_lst;

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
	float vert_distance;
	float horz_distance;
}t_distance;


typedef struct s_ray
{

	float	ray_angle;
	float	wallhit_x;
	float	wallhit_y;
	float	distance;
	bool	if_down;
	bool	if_up;
	bool	if_R;
	bool	if_L;
	bool	is_vert;
	bool 	is_horz;
} t_ray;

typedef struct s_win {
	void *mlx_win;
	int mouse_pointer_x;
	int columns;
	int lines;
} t_win;

typedef struct s_colors{
	int R;
	int G;
	int B;
} t_colors;

typedef struct s_textures{
	char *North;
	char *South;
	char *West;
	char *East;
} t_textures;
typedef struct s_img {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}t_img;

typedef struct s_map{
	char **map;
	int NbrOfRows;
	int NbrOfColumns;
	t_textures *textures;
	t_colors *FloorColor;
	t_colors *CeilingColor;
	t_img *wall;
	t_img *wall_2;
	t_ray *ray;
}t_map;


typedef struct s_player{
	float x;
	float y;
	float turnDirection;
	int walkDirection;
	float sideAngle;
	float initialAngle;
	float moveSpeed;
	float rotationSpeed;
}t_player;

typedef struct s_data{
	t_map *MapDisplay;
	t_win *win;
	t_player *player;
	t_img *img;
	void *mlx_ptr;
}t_data;

void error_message(char *message);
char	*ft_strchr(const char *s, int c);
void Parser(char *MapPath, t_data **Data);
void constructor(t_data **Data);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int ft_strlen(char *str);
char	**ft_split(char const *s, char c);
void free_array(char **arr);
bool ft_isspace(char c);
char	*ft_substr(char *s, int start, int len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s1);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
void	ft_lstadd_front(t_lst **lst, t_lst *new);
void ft_lstdelete(t_lst **lst);
t_lst	*ft_lstlast(t_lst *lst);
t_lst	*ft_lstnew(void *content);
int	ft_lstsize(t_lst *lst);
void ft_lstprint(t_lst **list);
int	ft_atoi(const char *str);
int ft_strisdigit(char *str);
void isMapValid(t_lst **maphead);
int	check_map_is_valid(t_data **data);
int	skip_space(char *str);
void draw_map(t_data **Data);
int close_win(t_data *Data);
int	key_press(int keycode, t_data **data);
void draw_minimap(t_data **Data);
int keyrelease(int keycode, t_data **data);
int handler(t_data **data);
void checkWallCollision(t_data **data);
int	is_valid_char(char c);
unsigned int	create_rgb(int r, int g, int b);
void			my_mlx_pixel_put(t_img *img, int x, int y,unsigned int color);
void			draw_square(t_data **data, int x, int y, unsigned long color);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				open_file(char *MapPath);
void			parser(char *MapPath, t_data **Data);
void    		cast_rays(t_data *data);
void	drawline(t_data **data, float dx, float dy);
void	init_mlx_loop(t_data **data);
void draw_in_window(t_data **data);
void draw_background(t_data **data, unsigned long floor_color, unsigned long ceiling_color);
void	move_player(t_data **data, t_player **player);
void	draw_player(t_data **data);
void intercept(t_data *data);
unsigned int my_mlx_pixel_get(t_img *img, int x, int y);
void *create_img(t_data *data,char *path);
//--------------------------------------------------------------------------------------//
void    free_linked_list(t_lst **head);
t_lst	*new_node(void *content);
void	add_node_back(t_lst **lst, t_lst *new);
t_lst    *get_last_node(t_lst *lst);
float normalize_angle(float angle);
void init_t_ray(t_ray **ray, float ray_angle);
#endif