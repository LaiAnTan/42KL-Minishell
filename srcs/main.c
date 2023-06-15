/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:30:54 by tlai-an           #+#    #+#             */
/*   Updated: 2023/06/14 10:44:02 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	init_data(t_data *data, char **envp)
{
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	data->cwd = getcwd(NULL, 1024);
	data->vars = set_env(envp);
	data->cmds = NULL;
	data->my_envp = NULL;
	data->attr = malloc(sizeof(struct termios) * 2);
	data->last_exit = 0;
	tcgetattr(STDIN_FILENO, &data->attr->def_attributes);
	rebuild_envp(data);
	return (1);
}

int	handle_line(t_data *data)
{
	char	*line;

	line = readline("\x1b[31;1m" "Minishell$ " "\x1b[m");
	if (line)
	{
		if (line[0] == '\0')
		{
			free(line);
			return (0);
		}
		add_history(line);
		rl_redisplay();
		data->line = ft_strdup(line);
		free(line);
		return (1);
	}
	else
		exit(reset_and_exit(&data->attr->def_attributes, 0));
}

void	cleanup(t_data *data)
{
	dup2(data->stdin_backup, STDIN_FILENO);
	dup2(data->stdout_backup, STDOUT_FILENO);
	if (data->cmds)
		ft_lstfree(&data->cmds);
	if (data->line)
		free(data->line);
}

int	error_msg(char *cmd, char *context, char *msg, int code)
{
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (context)
	{
		write(STDERR_FILENO, context, ft_strlen(context));
		write(STDERR_FILENO, ": ", 2);
	}
	write (STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (code);
}

int	main(int argc, char **argv, char **envp)
{
	t_data			data;

	(void)argv;
	if (argc != 1)
		return (0);
	init_data(&data, envp);
	tcgetattr(STDOUT_FILENO, &data.attr->mod_attributes);
	data.attr->mod_attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data.attr->mod_attributes);
	while (1)
	{
		signal(SIGINT, new_line_handler);
		signal(SIGQUIT, SIG_IGN);
		if (!handle_line(&data))
			continue ;
		replace_dollar(&data);
		lexer(&data);
		parser(&data);
		if (data.cmds)
			run_cmd(&data);
		cleanup(&data);
	}
	if (data.vars)
		ft_lstfree(&data.vars);
	return (reset_and_exit(&data.attr->def_attributes, 0));
}
