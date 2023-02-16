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

variable expansion		$
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
	while (src[len] != NULL)
		len++;
	new = (char **) malloc (sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = ft_strdup(src[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free_2d_array(src);
	return (new);
}

int	*find_token_pos(char *line, int last_token_end_pos)
{
	int		i;
	int		j;
	int		*index_pair;
	char	token[10] = "\'\"|>><<$? ";

	i = last_token_end_pos + 1;
	j = 0;
	index_pair = (int *) malloc (sizeof(int) * 2);
	if (!index_pair)
		return (NULL);
	while ((line[i] != '\0') && (line[i] == ' ' || line[i] == '\t'))
		i++;
	index_pair[0] = i;
	if (line[i] == '\0')
		return (NULL);
	while (line[i] != token[j])
		j++;
	if (j == 3 || j == 5 || j == 7) /* > < $ */
		if (line[i + 1] != '\0' && line[i + 1] == token[j + 1])
			index_pair[1] = i + 1;
		else
			index_pair[1] = i;
	else
		index_pair[1] = i;
	return (index_pair);
}

char	**lexer(char *line)
{
	int		len;
	int		end_pos;
	int		*token_pos;
	char	*new_token;
	char	**tokens;

	len = ft_strlen(line);
	
	token_pos = (int *) malloc (sizeof(int) * 2);
	tokens = (char **) malloc (sizeof(char *) * 1);
	if (!token_pos || !tokens)
		return (NULL);

	end_pos = 0;
	token_pos[0] = 0;
	token_pos[1] = 0;
	tokens[0] = NULL;
	
	while (end_pos <= len)
	{
		end_pos = token_pos[1];
		token_pos = find_token_pos(line, end_pos);
		if (!token_pos)
			break ;	
		new_token = ft_substr(line, token_pos[0], token_pos[1]);
		token_pos[0] = end_pos + 1;
		tokens = realloc_append(tokens, new_token);
		free(new_token);
	}
	free(token_pos);
	return (tokens);
}