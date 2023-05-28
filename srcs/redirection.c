#include "../headers/minishell.h"

/*
--redirection--

< should redirect input.
> should redirect output.
<< should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
>> should redirect output in append mode.

redirections are handled left to right no matter what

redirection identifier without a (*) filename is an error
(*) input redirection : existing filename only
(*) output redirection : existing / potential filename

eg: ls > a > b > c
output: files a, b and c are created, but the output is written only inside c

eg: cat < a < b < c
output: only file c is redirected as input

eg: cat < a << EOF < c
output: STDIN is read until EOF is found, only then file c is redirected as input

for multiple commands:
redirections should be done inside the child process, 
but before the alteration of the command's input and output
this is because redirections override piping

*/

void	handle_redir_input(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		printf("%s: file could not be open", filename); // handle later
		return (0);
	}
	dup2(fd, dup(STDIN_FILENO));
	close(fd);
	return (1);
}

void	handle_redir_input_delim(char *eof)
{
	// pipes
}

void	handle_redir_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		printf("%s: file could not be open", filename); // handle later
		return (0);
	}
	dup2(fd, dup(STDOUT_FILENO));
	close(fd);
	return (1);
}

void	handle_redir_output_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0777);
	if (fd == -1)
	{
		printf("%s: file could not be open", filename); // handle later
		return (0);
	}
	dup2(fd, dup(STDOUT_FILENO));
	close(fd);
	return (1);
}

int		is_redirect(char *arg)
{
	if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0 
		|| ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0)
	{
		return (1);
	}
	return (0);
}

int		contains_redirect(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;

	while (args[i + 1] != NULL)
	{
		if (is_redirect(args[i]))
			flag = 1;
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

int		get_redirect_type(char *arg)
{
	if (!is_redirect(arg))
		return (0);
	if (ft_strcmp(arg, ">") == 0)
		return (1);
	if (ft_strcmp(arg, ">>") == 0)
		return (2);
	if (ft_strcmp(arg, "<") == 0)
		return (3);
	if (ft_strcmp(arg, "<<") == 0)
		return (4);
}

int		*get_next_redirect(char **args, int index)
{
	int	*redirect_info; // 0 = type, 1 = index

	if (index >= count_2d_array(args))
		return (NULL);
	redirect_info = (int *) malloc(sizeof(int) * 2);
	while (args[index] != NULL)
	{
		redirect_info[0] = get_redirect_type(args[index]);
		if (redirect_info[0] != 0)
		{
			redirect_info[1] = index;
			return (redirect_info);
		}
		++index;
	}
	return (NULL);
}

char	**get_cmd_args_without_redirect(char **args)
{
	int		i;
	int		*redirect_info;

	char	**new;

	i = 0;
	redirect_info = get_next_redirect(args, 0);
	if (redirect_info == NULL)
		return (NULL);
	new = (char **) malloc(sizeof(char *) * redirect_info[1]);
	while (i < redirect_info[1]);
	{
		new[i] = ft_strdup(args[i]);
		++i;
	}
	new[i] = NULL;
	return (new);
}

// last arguement redirect error handled at the end
int		handle_redirect(char **args, t_data *data)
{
	if (!contains_redirect(args))
		return (0);
	
}