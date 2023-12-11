/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:45:30 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/03 23:39:57 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_single_quotes(char *line, int i)
{
	i++;
	while (line[i] && line[i] != '\'')
		i++;
	return (i);
}

int	expand_exit_status(char **line, int i, int exit_status)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(exit_status);
	if (!status)
		return (-1);
	(*line)[i] = '\0';
	(*line)[i + 1] = '\0';
	tmp = ft_strjoin(*line, *line + i + 2, 0);
	if (!tmp)
		return (-1);
	ft_strinserts(&tmp, status, i);
	if (!tmp)
		return (-1);
	free(*line);
	*line = tmp;
	return (i + ft_strlen(status));
}

int	expand_env_var(char **line, int i, char **ev, int j)
{
	char	*var;
	char	*value;
	char	*tmp;

	while ((*line)[j] && (*line)[j] != ' ' &&
			(*line)[j] != '\'' && (*line)[j] != '\"')
		j++;
	if (!(*line)[i + 1])
		return (i);
	var = ft_substr(*line, i + 1, j - i - 1);
	if (!var)
		return (-1);
	value = ev[k24(var)];
	free(var);
	(*line)[i] = '\0';
	tmp = ft_strjoin(*line, *line + j, 0);
	if (!tmp)
		return (-1);
	if (value)
		ft_strinserts(&tmp, value, i);
	if (!tmp)
		return (-1);
	free(*line);
	*line = tmp;
	return (i + ft_strlen(value));
}

// expand env variables and $? that is not inside single quotes
char	*expand_line(char *line, t_sh *sh)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = skip_single_quotes(line, i);
		if (line[i] == '$' && line[i + 1] == '?')
		{
			i = expand_exit_status(&line, i, sh->cl.exit_status);
			if (i == -1)
				return (NULL);
		}
		else if (line[i] == '$' && line[i + 1] != ' '
			&& line[i + 1] != '\'' && line[i + 1] != '\"' )
		{
			i = expand_env_var(&line, i, sh->ev, i + 1);
			if (i == -1)
				return (NULL);
		}
		i++;
	}
	return (line);
}
