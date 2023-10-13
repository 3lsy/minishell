/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:24:27 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 16:09:26 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** write_history: write line to history file
*/

static char	*ft_write_history(t_history *history, int fd, int size)
{
	char		*line;

	if (!history || size > HISTSIZE)
		return (NULL);
	line = ft_write_history(history->next, fd, size + 1);
	if (line)
		ft_fprintf(fd, "%s\n", line);
	return (history->line);
}

/*
 ** save history: open history file, write history to it, close history file
 */

void	save_history(t_sh *sh)
{
	int			fd;
	char		*line;

	fd = open(sh->history_path, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		exit_error(strerror(errno));
	line = ft_write_history(sh->history, fd, 1);
	if (line)
		ft_fprintf(fd, "%s\n", line);
	close(fd);
}
