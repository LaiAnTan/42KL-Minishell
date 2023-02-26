#include "../headers/minishell.h"

int	handle_line(t_data *data)
{
	char	*line;

	line = readline("\x1b[31;1m" "Mi" "\x1b[33;1m" "ni" 
					"\x1b[32;1m" "sh" "\x1b[36;1m" "el" 
					"\x1b[35m" "l$ " "\x1b[m");
	if (line && *line)
	{
		add_history(line);
		rl_redisplay();
		data->line = ft_strdup(line);
		free(line);
		return (1);

	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	(void *) envp;
	(void **) argv;
	if (argc != 1)
		return (0);

	t_data data;

	init_data(&data, envp);
	while (1)
	{
		handle_line(&data);
		lexer(&data);
		// expander(&data);
		parser(&data);
		for (int i = 0; data.tokens[i]; i++)
			printf("%d: %s\n", i, data.tokens[i]);
	}
}