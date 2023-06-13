/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:31:02 by tlai-an           #+#    #+#             */
/*   Updated: 2023/06/13 17:36:16 by cshi-xia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	modify_attr(t_data *data)
// {
// 	data->attr->mod_attributes.c_iflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &data->attr->mod_attributes);
// }

void	new_line_handler(int sig_code)
{
	(void) sig_code;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}
