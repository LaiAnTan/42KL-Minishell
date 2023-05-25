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

// hmm would this work
# define DO_NOT_IGNORE_SPACE !(*ignore_space) 

int	find_token_pos(char *line, int *index_pair, int *ignore_space)
{
	int		i;
	int		tk_type;

	// check if the index is on '\0' symbol, if it is kill it with fire
	if (index_pair[1] + 1 >= ft_strlen(line))
		return (0);
	i = index_pair[1] + 1;
	index_pair[0] = index_pair[1] + 1;
	// fuck you bunny ears
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (DO_NOT_IGNORE_SPACE)
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
		if (line[i] == '\'' || line[i] == '\"')
			// flip flop
			*ignore_space = (*ignore_space == 0);
	}
	// handles everything else
	else
	{
		while (line[i + 1] != '\0' && !is_token(line[i + 1]))
		{
			// this is a pain in the ass
			if (line[i + 1] == ' ' && DO_NOT_IGNORE_SPACE)
				break;
			i++;
		}
	}
	index_pair[1] = i;
	return (1);
}

// will now attempt to fix the "" this symbol
// expect horrendous code cause i lazy change

int	lexer(t_data *data)
{
	int		len;
	int		token_pos[2];
	char	*new_token;
	
	int		ignore_space;

	ignore_space = 0;
	len = ft_strlen(data->line);
	data->tokens = (char **) malloc (sizeof(char *));
	if (!data->tokens)
		return (0);
	token_pos[1] = -1;
	data->tokens[0] = NULL;
	while (1)
	{
		if (!find_token_pos(data->line, token_pos, &ignore_space) || token_pos[1] >= len)
			break ;
		new_token = ft_substr(data->line, token_pos[0], token_pos[1]);
		data->tokens = realloc_append(data->tokens, new_token);
		free(new_token);
	}

	printf("in tokens:\n");
	for (int i = 0; data->tokens[i]; ++i)
		printf("%d -- %s\n", i, data->tokens[i]);
	return (1);
}