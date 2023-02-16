#include "../headers/minishell.h"

void	handle_line()
{
	int		stop_sig;
	char	*line;

	stop_sig = 0;
	while (stop_sig == 0)
	{
		line = readline("> ");
		if (line && *line)
		{
			add_history(line);
			rl_redisplay();
		}
		// lexer(line);
	}
	clear_history();
	free(line);
	return ;
}

int main(void)
{
	char	**tk = lexer("$A >> cat -e | ls");
	for (int i = 0; i++; tk[i])
		printf("%s\n", tk[i]);
	free_2d_array(tk);
}