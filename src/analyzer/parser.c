/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:30:40 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/15 16:32:23 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_byte	is_operator(char *str, int i)
{
	if (!str || !str[i])
		return (127);
	if (ft_strcmp(str, ">>") == 0)
		return (DBL_R);
	else if (ft_strcmp(str, ">") == 0)
		return (SGL_R);
	else if (ft_strcmp(str, "<<") == 0)
		return (DBL_L);
	else if (ft_strcmp(str, "<") == 0)
		return (SGL_L);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	return (127);
}

t_bool	ft_parser(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		if (is_operator(tokens[i], 0) != 127 && !valid_position(tokens, i))
		{
			if (is_operator(tokens[i], 0) == PIPE)
				ft_fprintf(STDERR_FILENO, ERR_SYNTAX, "|");
			else
				ft_fprintf(STDERR_FILENO, ERR_SYNTAX, tokens[i]);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	is_redirection(char *token)
{
	if (is_operator(token, 0) != 127 && is_operator(token, 0) != PIPE)
		return (TRUE);
	return (FALSE);
}

/*
** Only verification for operator positions
** For pipes: if the token is a pipe, verify if at left there's a pipe or
** the beginning of the line, if so, ERROR.
** For redirections: if the token is a redirection, verify if at left there's
** a redirection, if so, ERROR.
*/

t_bool	valid_position(char **tokens, int i)
{
	if (!tokens[i + 1])
		return (FALSE);
	if (is_operator(tokens[i], 0) == PIPE
		&& (i == 0 || is_operator(tokens[i - 1], 0) != 127))
		return (FALSE);
	else if (is_redirection(tokens[i]) && i != 0
		&& is_redirection(tokens[i - 1]))
		return (FALSE);
	return (TRUE);
}
