/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:33:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/12 20:19:37 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

static int	heredoc_prompt(char *delimiter, int *pipe)
{
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, delimiter) == 0 || g_sigint == CTRLC)
		{
			free(line);
			return (g_sigint == NONE);
		}
		ft_fprintf(pipe[1], "%s\n", line);
		free(line);
		line = readline("> ");
	}
	free(line);
	return (0);
}

void	heredoc(t_sh *sh, char *delimeter)
{
	int	pipe_fd[2];
	int	eof;

	if (pipe(pipe_fd) < 0)
		exit_error(strerror(errno), sh);
	eof = heredoc_prompt(delimeter, pipe_fd);
	if (g_sigint == CTRLC || !eof)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return ;
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
}
