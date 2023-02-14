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

int main(int argc, char **argv, char **envp)
{
	(void) argv, envp;
	if (argc != 1) // args check
		return (0);
	handle_line();
	
}