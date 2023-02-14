#include "minishell.h"

/*
symbols to be handled

single quotation		'
double quotation		"
variable expansion		$
redirect input			<
redirect output			>
delimiter				<<
append					>>
pipes					|
exec status of last cmd	$?

else keyword

*/


int		count_tokens(char *line)
{

}

char	**lexer(char *line)
{
	int	tokens;

	tokens = count_tokens(line);
}