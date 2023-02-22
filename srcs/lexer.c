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
		{
			printf("found token %c\n", token[i]);
			return (i + 1);
		}
		i++;
	}
	return (0);
}

int	*find_token_pos(char *line, int last_end)
{
	int		i;
	int		tk_type;
	int		*index_pair;

	if (last_end >= ft_strlen(line))
		return (NULL);
	i = last_end;
	index_pair = (int *) malloc (sizeof(int) * 2);
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	index_pair[0] = i;
	tk_type = is_token(line[i]);
	// handles identifier
	if (tk_type != 0)
	{
		// handles  < and > 
		if (line[i + 1] != '\0' && (tk_type == 4 || tk_type == 5))
		{
			// handles << and >>
			if (tk_type == is_token(line[i + 1]))
				i++;
		}
		// handles $
		else if (line[i + 1] != '\0' && tk_type == 6)
		{
			// handles $?
			if (line[i + 1] == '?')
				i++;
		}
	}
	// handles everything else
	else
	{
		while (line[i + 1] != '\0' && line[i + 1] != ' ' && !is_token(line[i + 1]))
			i++;
	}
	index_pair[1] = i;
	printf(" %d | %d\n", index_pair[0], index_pair[1]);
	return (index_pair);
}

char	**lexer(char *line)
{
	int		end;
	int		*token_pos;
	char	*new_token;
	char	**tokens;
	
	token_pos = (int *) malloc (sizeof(int) * 2);
	tokens = (char **) malloc (sizeof(char *));
	if (!token_pos || !tokens)
		return (NULL);
	
	token_pos[1] = -1;
	tokens[0] = NULL;

	while (1)
	{
		end = token_pos[1];
		token_pos = find_token_pos(line, end + 1);
		if (!token_pos)
			break ;
		new_token = ft_substr(line, token_pos[0], token_pos[1]);
		printf("new token created: %s\n", new_token);
		tokens = realloc_append(tokens, new_token);
		free(new_token);
	}
	free(token_pos);
	return (tokens);
}