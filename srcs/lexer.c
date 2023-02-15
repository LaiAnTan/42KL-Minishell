#include "../headers/minishell.h"

/*
symbols to be handled

single quotation		'
double quotation		"
pipes					|

redirect input			<
redirect output			>
delimiter				<<
append					>>

variable expansion		
$
exec status of last cmd	$?
else keyword

*/

char	**realloc_append(char **src, char *str)
{
	int		i;
	int		len;
	char	**new;

	i = 0;
	len = 0;
	while (src[len++]) {}
	new = (char **) malloc (sizeof(char *) * (len + 1));
	while (src[i])
		new[i] = ft_strdup(src[i++]);
	new[i] = ft_strdup(str);
	free_2d_array(src);
	return (new);
}

char	**lexer(char *line)
{
	int		i;
	int		len;

	char	*new_token;
	char	**tokens;

	i = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\t' || line[i] != ' ')
			i++;
		new_token = ft_substr(line, i, len);
		tokens = realloc_append(tokens, new_token);
		free(new_token);
	}
	free(line);
	return (tokens);
}