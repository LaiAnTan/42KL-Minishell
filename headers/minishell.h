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

/* Lexer */
char	**lexer(char *line);

/* Lexer helper functions */
int	*find_token_pos(char *line, int last_token_end_pos);

char	**realloc_append(char **src, char *str);

/* Builtin command functions */
void	builtin_echo(char *str, char option);
void	builtin_cd(char *path, char type);
void	builtin_pwd(t_data *data);


void	builtin_env(char **envp);
void	builtin_exit(t_data *data);


/* Utility functions */
void	free_2d_array(char **a);

int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);

char	*ft_strdup(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif