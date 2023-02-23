#include "../headers/minishell.h"

#define MAGENTA "\x1b[35m"
#define YELLOW "\x1b[33m"
#define NORMAL "\x1b[m"

int	handle_line(t_data *data)
{
	char	*line;

	line = readline(YELLOW "Mini" MAGENTA "shell: " NORMAL);
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
	ft_lstprint(data.vars);
	while (1)
	{
		handle_line(&data);
		lexer(&data);
		// expander(&data);
		for (int i = 0; data.tokens[i]; i++)
			printf("%d: %s\n", i, data.tokens[i]);
	}
}