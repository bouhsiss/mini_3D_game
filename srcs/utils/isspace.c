#include "cub3D.h"

bool isspace(char c)
{
	if(c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\v' || c == '\f' || c == '\r')
		return(true);
	else
		return(false);
}