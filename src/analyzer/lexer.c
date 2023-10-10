/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:34:42 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/10 17:20:55 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO:
// exit_error checked
char	**ft_lexer(t_sh *sh)
{
	char	**line;

	sh->cui.line = insert_spaces(sh->cui.line);
	if (!sh->cui.line)
		exit_error(strerror(errno), sh);
	sh->cui.line = expand_line(sh->cui.line, sh);
	// ft_printf("Expanded line: %s\n", sh->cui.line);
	if (!sh->cui.line)
		exit_error(strerror(errno), sh);
	line = ft_split_args(sh->cui.line);
	if (!line && errno != EINVAL)
		exit_error(strerror(errno), sh);
	else if (!line)
	{
		ft_fprintf(STDERR_FILENO, ERR_UNC_QUOTE);
		return (NULL);
	}
	return (line);
}

t_byte	is_operator(char *str, int i)
{
	if (!str || !str[i])
		return (127);
	if (str[i] == '>' && str[i + 1] == '>')
		return (DBL_R);
	else if (str[i] == '>' && str[i + 1] != '>')
		return (SGL_R);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (DBL_L);
	else if (str[i] == '<' && str[i + 1] != '<')
		return (SGL_L);
	else if (str[i] == '|')
		return (PIPE);
	return (127);
}

char	*insert_spaces(char *str)
{
	int		i;
	t_byte	token;

	i = 0;
	while (str && str[i])
	{
		token = is_operator(str, i);
		if (token != 127)
		{
			ft_strinsert(&str, ' ', i++);
			if (!str)
				return (NULL);
			if (token == DBL_R || token == DBL_L)
				i++;
			if (!str[i])
				break ;
			if (str[i + 1])
				ft_strinsert(&str, ' ', i + 1);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}
