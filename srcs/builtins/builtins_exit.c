/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:31:52 by tlai-an           #+#    #+#             */
/*   Updated: 2023/06/14 10:42:26 by tlai-an          ###   ########.fr       */
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
	{
		printf("exit: too many arguements\n");
		return (1);
	}
	else if (args[1] == NULL)
		exit_code = 0;
	else if (!is_numeric(args[1]))
	{
		printf("exit: %s: numeric arguement required", args[1]);
		exit_code = 2;
	}
	else
		exit_code = ft_atoi(args[1]);
	while (exit_code >= 256)
		exit_code = exit_code - 256;
	printf("process exited with code %d\n", exit_code);
	return (reset_and_exit(&data->attr->def_attributes, exit_code));
}
