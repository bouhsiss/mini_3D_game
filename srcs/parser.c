#include "cub3D.h"

static int open_file(char *MapPath) {
	int fd;

	if(open(MapPath, O_DIRECTORY) > 0)
		ErrorMessage("map should be a file not a directory.");
	if(ft_strcmp(ft_strchr(MapPath,'.'), ".cub"))
		ErrorMessage("map should have .cub extension");
	fd = open(MapPath, O_RDONLY);
	if(fd == -1)
		ErrorMessage(strerror(errno));
	return(fd);
}


static void readFile(char *MapPath, t_data **Data) {
	int fd;
	char *tmp;
	char *p;
	char **arr;

	fd = open_file(MapPath);
	(*Data)->win->columns = 0;
	tmp = get_next_line(fd);
	p = tmp;
	while (tmp)
	{
		tmp = get_next_line(fd);
		if(tmp)
			p = ft_strjoin(p,tmp);
		free(tmp);
	}
	close(fd);
	arr = ft_split(p, '\n');
	//parse file
	//is map valid
	free(p);
}

void Parser(char *MapPath, t_data **Data)
{
	readFile(MapPath, Data);
}