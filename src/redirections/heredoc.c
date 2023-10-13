/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:33:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 16:09:07 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_prompt(char *delimiter, int *pipe)
{
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(pipe[1]);
			exit(EXIT_SUCCESS);
		}
		ft_fprintf(pipe[1], "%s\n", line);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(pipe[1]);
	exit(CTRLD);
}

static void	execute_in_context(int *pipe_fd, char *delimeter)
{
	int	sig_bkp;

	sig_bkp = g_sigint;
	g_sigint = 0;
	ft_signals(HEREDOC);
	close(pipe_fd[0]);
	heredoc_prompt(delimeter, pipe_fd);
	g_sigint = sig_bkp;
	ft_signals(EXEC);
}

static void	heredoc_error(char *delimeter, t_sh *sh)
{
	ft_printf("minishell: warning: here-document delimited by end-of-file ");
	ft_printf("(wanted `%s')\n", delimeter);
	sh->cl.exit_status = 1;
}

static int	parent_heredoc(t_sh *sh, int *pipe_fd, pid_t pid, char *delimeter)
{
	int		status;

	close(pipe_fd[1]);
	waitpid(pid, &sh->cl.exit_status, 0);
	status = WEXITSTATUS(sh->cl.exit_status);
	if (status == CTRLD)
		heredoc_error(delimeter, sh);
	if (status != EXIT_SUCCESS)
	{
		close(pipe_fd[0]);
		return (status);
	}
	return (EXIT_SUCCESS);
}

int	heredoc(t_sh *sh, char *delimeter, int isbuiltin)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) < 0)
		exit_error(strerror(errno));
	pid = fork();
	if (pid < 0)
		exit_error(strerror(errno));
	if (pid == 0)
		execute_in_context(pipe_fd, delimeter);
	status = parent_heredoc(sh, pipe_fd, pid, delimeter);
	if (status == EXIT_SUCCESS)
	{
		if (isbuiltin)
			close(pipe_fd[0]);
		else
			dup2(pipe_fd[0], STDIN_FILENO);
	}
	return (status);
}
