/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:33:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 19:23:32 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_prompt(char *delimiter, int *pipe)
{
	char	*line;

	ft_printf("> ");
	line = ft_get_next_line(0);
	while (line)
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_get_next_line(-503);
			break ;
		}
		ft_fprintf(pipe[1], "%s\n", line);
		free(line);
		ft_printf("> ");
		line = ft_get_next_line(0);
	}
	free(line);
}

/*
** Here document redirection: <<
** Opens a simple prompt to take input from the user, until the user types
** the delimiter. The input is then redirected to the command's STDIN.
** Using a pipe to send the input to the command.
*/

void	heredoc(t_sh *sh, char *delimeter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		exit_error(strerror(errno), sh);
	heredoc_prompt(delimeter, pipe_fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
}
