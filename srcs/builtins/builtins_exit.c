/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:31:52 by tlai-an           #+#    #+#             */
/*   Updated: 2023/06/19 12:58:59 by cshi-xia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	reset_and_exit(struct termios *saved, int exit_code)
{
	reset_attr(saved);
	exit(exit_code);
}

int	builtin_exit(t_data *data, char **args)
{
	int		exit_code;

	if (count_2d_array(args) > 2)
		return (error_msg("exit", NULL, "too many arguments", 1));
	else if (args[1] == NULL)
		exit_code = 0;
	else if (!is_numeric(args[1]))
		exit_code = error_msg("exit", args[1], "numeric argument required", 2);
	else
		exit_code = ft_atoi(args[1]);
	while (exit_code >= 256)
		exit_code = exit_code - 256;
	printf("exit\n");
	return (reset_and_exit(&data->attr->def_attributes, exit_code));
}
