#include "../headers/minishell.h"

int	handle_line(t_data *data)
{
	char	*line;

	line = readline("\x1b[31;1m" "Gay" "\x1b[33;1m" "as" 
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

// prints out content in lst
void	print_parsed(t_list *amogus)
{
	t_list *iter;
	int		iter_count;

	iter_count = 1;
	iter = amogus;
	while (iter)
	{
		printf("%d cmd = \n", iter_count);
		for (int i = 0; iter->cmd.cmd[i]; ++i)
			printf("%d | %s\n", i, iter->cmd.cmd[i]);
		iter = iter->next;
		++iter_count;
	}
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
		if (!handle_line(&data))
			continue;
		lexer(&data);
		for (int i = 0; data.tokens[i]; i++)
			printf("%d: %s\n", i, data.tokens[i]);
		// expander(&data);
		parser(&data);
		printf("parsed stuff = \n");
		print_parsed(data.cmds);
		ft_lstfree(&data.cmds);
		free(data.line);
	}
}