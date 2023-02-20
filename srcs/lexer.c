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

int	is_token(char c)
{
	int		i = 0;
	char	token[9] = "\'\"|><$";
	
	while (token[i] != '\0')
	{
		if (token[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

int	*find_token_pos(char *line, int last_token_end_pos)
{
	int		i;
	int		tk_type;
	int		*index_pair;

	if (last_token_end_pos >= ft_strlen(line))
		return (NULL);
	if (last_token_end_pos != 0)
		i = last_token_end_pos + 1;
	index_pair = (int *) malloc (sizeof(int) * 2);
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (i == ft_strlen(line))
		return (NULL);
	index_pair[0] = i;
	tk_type = is_token(line[i]);
	if (tk_type != 0)
	{
		if (line[i + 1] != '\0' && (tk_type == 4 || tk_type == 5))
		{
			if (tk_type == is_token(line[i + 1]))
				i++;
		}
		else if (line[i + 1] != '\0' && tk_type == 6)
		{
			if (line[i + 1] == '?')
				i++;
		}
	}
	else
	{
		while (line[i] != '\0' && line[i] != ' ' && is_token(line[i]) == 0)
			i++;
	}
	index_pair[1] = i;
	printf("start: %d | end: %d\n", index_pair[0], index_pair[1]);
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
	tokens = (char **) malloc (sizeof(char *));
	if (!token_pos || !tokens)
		return (NULL);
	
	token_pos[1] = 0;
	end_pos = 0;
	tokens[0] = NULL;

	while (end_pos <= len)
	{
		end_pos = token_pos[1];
		token_pos = find_token_pos(line, end_pos);
		if (!token_pos)
			break ;
		if (token_pos[0] == token_pos[1])
			new_token = ft_substr(line, token_pos[0], 1);
		else
			new_token = ft_substr(line, token_pos[0], token_pos[1] - token_pos[0]);
		printf("new token created: %s~\n", new_token);
		tokens = realloc_append(tokens, new_token);
		free(new_token);
	}
	free(token_pos);
	return (tokens);
}