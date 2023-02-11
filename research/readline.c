#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
tests for:
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
*/

int main(void)
{
	char *line;

	while (strlen(line) != 0)
	{
		line = readline("> ");
		add_history(line);
	}
	rl_clear_history();
}