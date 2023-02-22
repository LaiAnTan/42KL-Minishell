#include "../headers/minishell.h"

void	handle_line()
{
	int		stop_sig;
	char	*line;
	char	**tk;

	stop_sig = 0;
	while (stop_sig == 0)
	{
		line = readline("> ");
		if (line && *line)
		{
			add_history(line);
			rl_redisplay();
		}
		tk = lexer(line);
		free_2d_array(tk);
	}
	clear_history();
	free(line);
	return ;
}

int main(int argc, char **argv, char *envp)
{
	int		i = 0;
	(void *) envp;
	char	*line;

	if (argc != 1)
		return (0);
	handle_line();
}