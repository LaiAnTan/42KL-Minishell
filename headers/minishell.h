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

typedef struct s_env
{
	char			*str;
	int				printed;
}		t_env;

typedef struct s_cmd
{
	char			**cmd;
}		t_cmd;

typedef struct s_list
{
	t_env			env;
	t_cmd			cmd;
	struct s_list	*next;

}		t_list;

typedef struct s_data
{

	char	*line;
	char	**tokens;
	char	**my_envp;

	t_list	*vars;
	t_list	*cmds;
}			t_data;

/* Data */
void	rebuild_envp(t_data *data);

int 	init_data(t_data *data, char **envp);

/* Lexer */
int		lexer(t_data *data);

/* Expander */
int		expander(t_data *data);

/* Parser */
int		parser(t_data *data);

/* Command Path */
void	append_stuff(char **paths, char *cmd);

char	*get_path_envp(t_data *data);
char	**get_cmd_path(t_data *data, char *cmd);
char	*trim_path(char *path);

/* Commands Execution */
void	run_cmd(t_data *data, char *cmd_with_params);
int		exec_cmd(t_data *data, char *cmd, char **cmd_paths, char **args);

/* Environment Variables */
t_list	*set_env(char **envp);

int		get_equal_pos(t_list *node);

/* Builtin command functions */
void	builtin_echo(int argc, char **args, t_data *data);
void	builtin_cd(int argc, char **args, t_data *data);
void	builtin_pwd(int argc, char **args, t_data *data);
void	builtin_export(int argc, char **args, t_data *data);
void	builtin_unset(int argc, char **args, t_data *data);
void	builtin_env(int argc, char **args, t_data *data);
void	builtin_exit(int argc, char **args, t_data *data);

int		handle_builtins(int argc, char **args, t_data *data);

/* Error Handling */


/* Utility Functions */
void	free_2d_array(char **arr);

int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);

char	*ft_strdup(char *str);
char	*ft_append(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, unsigned int end);
char	**ft_split(char *s, char c);
char	**realloc_append(char **src, char *str);

/* Linked List */
t_list	*ft_lstnew_env(char *var);
t_list	*ft_lstnew_cmd(char **cmd);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstprint(t_list *lst);
void	ft_lstfree(t_list *lst);

int		ft_lstsize(t_list *lst);

#endif