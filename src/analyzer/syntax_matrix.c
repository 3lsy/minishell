/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:46:28 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/26 23:00:09 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** [["cmd", "arg", "redir", "filename", "arg"], 
**  ["cmd", "arg", "redir", "filename", "arg"], ...]
*/

int	count_pipes(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

int	ft_tokenslen(char **tokens, char *end)
{
	int	i;

	i = 0;
	while (tokens[i] && ft_strcmp(tokens[i], end) != 0)
		i++;
	return (i);
}

char	**tokens_until_pipe(char **tokens)
{
	char	**new;
	int		i;
	int		len;

	i = 0;
	len = ft_tokenslen(tokens, "|");
	new = ft_calloc(sizeof(char *), len + 1);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = tokens[i];
		i++;
	}
	return (new);
}

/*
** 1. Count pipes
** 2. Allocate memory for (# of pipes + 2) arrays
** 3. Use a function to create an array of tokens until next pipe
** 4. Append the array to the array of arrays iteratively
*/

char	***ft_split_cmds(char **tokens)
{
	char	***new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = count_pipes(tokens);
	new = ft_calloc(sizeof(char **), len + 2);
	if (!new)
		return (NULL);
	while (i <= len)
	{
		new[i] = tokens_until_pipe(&tokens[j]);
		j += ft_tokenslen(&tokens[j], "|") + 1;
		i++;
	}
	return (new);
}
