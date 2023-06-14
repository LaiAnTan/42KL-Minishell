/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:37:03 by tlai-an           #+#    #+#             */
/*   Updated: 2023/06/13 11:58:33 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_redirect(char *arg)
{
	if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0
		|| ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0)
	{
		return (1);
	}
	return (0);
}

int	contains_redirect(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (is_redirect(args[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_redirect_type(char *arg)
{
	if (!is_redirect(arg))
		return (0);
	if (ft_strcmp(arg, ">") == 0)
		return (1);
	if (ft_strcmp(arg, ">>") == 0)
		return (2);
	if (ft_strcmp(arg, "<") == 0)
		return (3);
	if (ft_strcmp(arg, "<<") == 0)
		return (4);
	return (-1);
}

int	file_not_found_error(char *filename)
{
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	return (-1);
}

int	file_cant_open_error(char *filename)
{
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, ": File could not be opened\n", 28);
	return (-1);
}
