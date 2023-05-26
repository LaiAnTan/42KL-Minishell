#include "../headers/minishell.h"

int	handle_line(t_data *data)
{
	char	*line;

	line = readline("\x1b[31;1m" "Minishell$ " "\x1b[m");
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

// debug function for printing commands
void	print_parsed(t_list *amogus)
{
	t_list *iter;
	int		iter_count;

	iter_count = 1;
	iter = amogus;
	while (iter)
	{
		printf("<Cmd %d>\n", iter_count);
		for (int i = 0; iter->cmd.cmd[i]; ++i)
			printf("%d | %s\n", i, iter->cmd.cmd[i]);
		iter = iter->next;
		++iter_count;
	}
}

void	cleanup(t_data *data) // i am going to throw some hands
{
	reset_attr(data);
	printf("attr resetted\n");
	if (data->vars)
	ft_lstfree(data->vars);
	printf("env list freed\n");
	if (data->cmds)
		ft_lstfree(&data->cmds);
	printf("cmd list freed\n");
	if (data->tokens)
		free_2d_array(&data->tokens);
	printf("tokens freed\n");
	if (data->my_envp)
		free_2d_array(&data->my_envp);
	printf("my_envp freed\n");
	if (data->cwd)
		free(data->cwd);
	printf("cwd freed\n");
}

int main(int argc, char **argv, char **envp)
{
	(void) argv;
	t_data data;

	if (argc != 1)
		return (0);
	init_data(&data, envp);
	modify_attr(&data);
	while (1)
	{
		signal(SIGINT, new_line);
		signal(SIGQUIT, SIG_IGN);
		if (!handle_line(&data))
			continue;
		lexer(&data);
		expander(&data);
		parser(&data);
		print_parsed(data.cmds);
		run_cmd(&data);
		ft_lstfree(&data.cmds);
		free(data.line);
	}
	cleanup(&data);
	return (0);
}