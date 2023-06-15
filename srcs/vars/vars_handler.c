/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:31:06 by tlai-an           #+#    #+#             */
/*   Updated: 2023/06/15 17:02:42 by cshi-xia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_keyword(char *line, int stop)
{
	++stop;
	while (line[stop] && line[stop] != ' '
		&& !is_token(line[stop]) && line[stop] != '$')
		++stop;
	return (--stop);
}

void	reset(char **temp_strings, int *indexes)
{
	int	i;

	indexes[1] = ft_strlen(temp_strings[0]) + ft_strlen(temp_strings[3]) - 1;
	i = -1;
	while (temp_strings[++i])
		free(temp_strings[i]);
}

void	break_down(char *line, int *indexes, char **temp_strings)
{
	indexes[2] = get_keyword(line, indexes[1]);
	if (indexes[1] != indexes[0])
		temp_strings[0] = ft_substr(line, indexes[0], indexes[1] - 1);
	else
		temp_strings[0] = NULL;
	temp_strings[1] = ft_substr(line, indexes[1] + 1, indexes[2]);
	temp_strings[2] = ft_substr(line, indexes[2] + 1, ft_strlen(line));
}

void	recombine_and_reset(char **store, char **temp_strings, int *indexes)
{
	char	*ret;

	if ((*store))
		free((*store));
	ret = NULL;
	ret = ft_append(ret, temp_strings[0]);
	ret = ft_append(ret, temp_strings[3]);
	ret = ft_append(ret, temp_strings[2]);
	(*store) = ret;
	reset(temp_strings, indexes);
}

int	one_side(char *line, int i, int in_ears)
{
	int	left;
	int	right;

	left = (line[i - 1] != '\'' && line[i - 1] != '\"');
	if (!in_ears)
		right = (line[i + 1] == '\'' || line[i + 1] == '\"');
	else
		right = (!is_token(line[i + 1]) && line[i + 1] != ' ');
	return (left && right);
}

char	*handle_special_case(char *line, int index, int special_case)
{
	if (one_side(line, index, special_case))
		return (ft_strdup(""));
	else
		return (ft_strdup("$"));
}

// else if (ret[indexes[1]] == '\'' && !special_case)
// {
// 	++indexes[1];
// 	while (ret[indexes[1]] && ret[indexes[1]] != '\'')
// 		++indexes[1];
// }

// if (one_side(ret, indexes[2], special_case))
// 	string_storage[3] = ft_strdup("");
// else
// 	string_storage[3] = ft_strdup("$");

void	rd_init_variables(int *special_case, char **string_storage, int *indexes)
{
	(*special_case) = 0;
	indexes[0] = 0;
	indexes[1] = 0;
	string_storage[4] = NULL;
}

void	replace_dollar(t_data *data)
{
	int		special_case;
	char	*ret;
	char	*string_storage[5];
	int		indexes[3];

	rd_init_variables(&special_case, string_storage, indexes);
	ret = ft_strdup(data->line);
	while (search_symbol(&ret[indexes[1]], '$') != -1)
	{
		if (ret[indexes[1]] == '\"')
			special_case = !special_case;
		else if (ret[indexes[1]] == '\'' && !special_case)
			indexes[1] = bunny_ears(ret, indexes[1], '\'');
		else if (ret[indexes[1]] == '$')
		{
			break_down(ret, indexes, string_storage);
			if (indexes[2] == indexes[1])
				string_storage[3] = handle_special_case(ret, indexes[2], special_case);
			else
				string_storage[3] = access_var(data, string_storage[1]);
			recombine_and_reset(&ret, string_storage, indexes);
		}
		++indexes[1];
	}
	free(data->line);
	data->line = ret;
}
