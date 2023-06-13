/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:31:02 by tlai-an           #+#    #+#             */
/*   Updated: 2023/06/13 15:01:11 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	modify_attr(t_data *data)
{
	data->attr->mod_attributes.c_iflag &= ~(ICANON | ECHO | ISIG);
	data->attr->mod_attributes.c_cc[VMIN] = 1;
	data->attr->mod_attributes.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->attr->mod_attributes);
}

void	reset_attr(t_data *data)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &data->attr->def_attributes);
}

void	new_line_handler(int sig_code)
{
	(void) sig_code;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}
