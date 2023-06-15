#include "../../headers/minishell.h"

int	get_keyword(char *line, int stop)
{
	++stop;
	while (line[stop] && line[stop] != ' '
		&& !is_token(line[stop]) && line[stop] != '$')
		++stop;
	return (--stop);
}