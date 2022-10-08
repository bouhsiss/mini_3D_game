#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct s_lst
{
	void *content;
	struct s_lst *next;
}t_lst;

typedef struct s_win {
	void *mlx_win;
	int columns;
	int lines;
} t_win;

typedef struct s_textures{
	char *North;
	char *South;
	char *West;
	char *East;
	char *FloorColor;
	char *CeilingColor;
}t_textures;

typedef struct s_data{
	t_lst *map;
	t_textures *textures;
	t_win *win;
}t_data;

void ErrorMessage(char *message);
char	*ft_strchr(const char *s, int c);
int	ft_strcmp(char *s1, char *s2);
void Parser(char *MapPath, t_data **Data);
void constructor(t_data **Data);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int ft_strlen(char *str);
char	**ft_split(char const *s, char c);

#endif