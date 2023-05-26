# include "../headers/minishell.h"

void	modify_attr(t_data *data)
{
	data->attr->mod_attributes.c_iflag &= ~(ISIG | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->attr->mod_attributes);
}

void	reset_attr(t_data *data)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &data->attr->def_attributes);
}

void	new_line(int sig_code)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}