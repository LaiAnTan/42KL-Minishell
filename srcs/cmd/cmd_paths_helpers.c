#include "../../headers/minishell.h"

int	is_executable(char *str)
{
	if (ft_strlen(str) > 2 && str[0] == '.' && str[1] == '/')
		return (1);
	return (0);
}

int	is_absolute(char *str)
{
	if (ft_strlen(str) > 2 && str[0] == '/')
		return (1);
	return (0);
}