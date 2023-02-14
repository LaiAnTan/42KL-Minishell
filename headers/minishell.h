#ifndef MINISHELL_H

#define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>

# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	char	*curr_path;
	
}			t_data;

/* Builtin command functions */
void	builtin_echo(char *str, char option);
void	builtin_cd(char *path, char type);
void	builtin_pwd(t_data *data);
-
-
void	builtin_env(char **envp);
void	builtin_exit(t_data *data);

/* Utility functions */
int		ft_strcmp(char *s1, char *s2);

#endif