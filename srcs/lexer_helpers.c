#include "../headers/minishell.h"

int	is_token(char c)
{
	int		i;
	char	token[6];

	i = 0;
	token[0] = '\'';
	token[1] = '\"';
	token[2] = '|';
	token[3] = '>';
	token[4] = '<';
	token[5] = '\0';
	while (token[i] != '\0')
	{
		if (token[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}
