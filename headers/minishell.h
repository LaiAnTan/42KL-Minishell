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

typedef struct s_list
{
	char			*str;
	struct s_list	*next;

}		t_list;

typedef struct s_data
{

	// tokens
	char	*line;
	char	**tokens;

	// variables
	t_list *vars;

	// directory path
	char	*curr_path;
}			t_data;

/* Data */
int 	init_data(t_data *data, char **envp);

/* Lexer */
int		lexer(t_data *data);

/* Lexer helper functions */
int		find_token_pos(char *line, int *token_pos);

/* Expander */
int		expander(t_data *data);

/* Environment Variables */
t_list	*set_env(char **envp);
int		get_equal_pos(t_list *node);

/* Builtin command functions */
void	builtin_echo(char *str, char option);
void	builtin_cd(char *path, char type);
void	builtin_pwd(t_data *data);
void	builtin_export(t_data *data, char **args);

void	builtin_env(t_data *data);
void	builtin_exit(t_data *data);

/* Utility functions */
void	free_2d_array(char **arr);

int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);

char	*ft_strdup(char *str);
char	*ft_substr(char *s, unsigned int start, unsigned int end);
char	**realloc_append(char **src, char *str);

/* Linked List */
t_list	*ft_lstnew(char *var);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstcpy(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstprint(t_list *lst);
void	ft_lstfree(t_list *lst);

int		ft_lstsize(t_list *lst);

#endif