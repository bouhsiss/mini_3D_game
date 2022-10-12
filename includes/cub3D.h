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

#define PARSE_MAP 0
#define NEXT_LINE 1
#define ONE_OR_SPACE(c) ((c == '1' || ft_isspace(c)) ? true : false)

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
	int B;;
} t_colors;

typedef struct s_textures{
	char *North;
	char *South;
	char *West;
	char *East;
} t_textures;

typedef struct s_map{
	t_lst* map;
	int NbrOfRows;
	int NbrOfColumns;
	t_textures *textures;
	t_colors *FloorColor;
	t_colors *CeilingColor;
}t_map;

typedef struct s_data{
	t_map *MapDisplay;
	t_win *win;
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
void DrawMap(t_data **Data);
int closeWin(t_data *Data);

#endif