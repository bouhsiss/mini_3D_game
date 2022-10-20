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

# define PI 3.14159265
# define DEGREE 3.14159265/180
# define RESOLUTION 20
# define RADIUS 5
# define NORTH 0*DEGREE
# define EAST 90*DEGREE
# define SOUTH 180*DEGREE
# define WEST 270*DEGREE
# define LINE_LENGTH 60
# define FOV 60*DEGREE
# define S_KEY 1
# define A_KEY 2
# define W_KEY 13
# define D_KEY 0
# define RIGHT_ARROW 123
# define LEFT_ARROW 124
typedef struct s_lst
{
	void *content;
	struct s_lst *next;
	struct s_lst *previous;
}t_lst;

typedef struct s_win {
	void *mlx_win;
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

typedef struct s_map{
	char **map;
	int NbrOfRows;
	int NbrOfColumns;
	t_textures *textures;
	t_colors *FloorColor;
	t_colors *CeilingColor;
}t_map;

typedef struct s_img {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}t_img;

typedef struct s_player{
	double x;
	double y;
	int height;
	int turnDirection;
	int walkDirection;
	double sideAngle;
	double initialAngle;
	float moveSpeed;
	double rotationSpeed;
}t_player;

typedef struct s_data{
	t_map *MapDisplay;
	t_win *win;
	t_player *player;
	t_img *img;
	void *mlx_ptr;
}t_data;

void ErrorMessage(char *message);
char	*ft_strchr(const char *s, int c);
void Parser(char *MapPath, t_data **Data);
void constructor(t_data **Data);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int ft_strlen(char *str);
char	**ft_split(char const *s, char c);
void freeArray(char **arr);
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
int closeWin(t_data *Data);
int	move_player(int keycode, t_data **data);
void draw_mini_map(t_data **Data);
int keyrelease(int keycode, t_data **data);
int handler(t_data **data);
void checkWallCollision(t_data **data);
int	is_valid_char(char c);
unsigned long	create_rgb(int r, int g, int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	put_square_in_image(t_data **data, int x, int y, unsigned long color);


#endif