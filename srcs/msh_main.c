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
		printf("%d\n", ft_strlen(line));
		for (int i = 0; tk[i] != NULL; i++)
			printf("%s\n", tk[i]);
		free_2d_array(tk);
	}
	clear_history();
	free(line);
	return ;
}

int main(int argc, char **argv, char *envp)
{
<<<<<<< HEAD
	int		i = 0;
	(void *) envp;
	char	*line;

	if (argc != 1)
		return (0);
	handle_line();
=======
	char	**tk = lexer("$A >> cat -e | ls");
	for (int i = 0; i++; tk[i])
		printf("%s\n", tk[i]);
	free_2d_array(tk);
>>>>>>> refs/remotes/origin/main
}