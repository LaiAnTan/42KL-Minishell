#ifndef MINISHELL_H

#define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <linux/limits.h>
# include <signal.h>
# include <termios.h>

# define TRUE 1
# define FALSE 0

// struct for environment variables
typedef struct s_env
{
	char			*str;
	int				printed;
}		t_env;

// struct for commands
typedef struct s_cmd
{
	char			**cmd;

}		t_cmd;

// linked list that holds environmental variables and commands (shit name)
typedef struct s_list
{
	t_env			env;
	t_cmd			cmd;
	struct s_list	*next;

}		t_list;

// all data for program
typedef struct s_data
{
	char	*line;
	char	*cwd;
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

/* Command Execution */
void	run_cmd(t_data *data);

int		exec_cmd(t_data *data, char **cmd_paths, char **args);

/* Environment Variables */
t_list	*set_env(char **envp);

int		get_equal_pos(t_list *node);

char	*get_val(t_list *node);

/* Builtin command functions */
void	builtin_echo(char **args, t_data *data);
void	builtin_cd(char **args, t_data *data);
void	builtin_pwd(char **args, t_data *data);
void	builtin_export(char **args, t_data *data);
void	builtin_unset(char **args, t_data *data);
void	builtin_env(t_data *data);
void	builtin_exit(char **args, t_data *data);

int		handle_builtins(char *cmd, char **args, t_data *data);

/* Error Handling */


/* Utility Functions */
void	free_2d_array(char ***arr);

int		is_numeric(char *str);
int		count_double(char **e);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2); // returns 0 if same
int		ft_strcmp_equals(char *s1, char *s2);
int		ft_atoi(const char *s);

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
void	ft_lstprint_env(t_list *lst);
void	ft_lstfree(t_list **lst);

int		ft_lstsize(t_list *lst);


// chua was here
int	get_keyword(char *line, int stop);

#endif