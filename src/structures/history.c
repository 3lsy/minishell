/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:35:37 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/17 18:58:31 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** create_history_node: create a new node with line
*/

t_history	*create_history_node(void)
{
	t_history	*new;

	new = ft_calloc(sizeof(t_history), 1);
	if (!new)
		return (NULL);
	new->line = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/*
** save line history: append line to history double linked list
*/

void	save_line_history(t_history **history, t_sh *sh, char *line)
{
	t_history	*history_node;

	history_node = create_history_node();
	if (!history_node)
		exit_error(strerror(errno), sh);
	history_node->line = ft_strdup(line);
	if (!history_node->line)
		exit_error(strerror(errno), sh);
	history_node->next = (*history);
	if (*history)
		(*history)->prev = history_node;
	(*history) = history_node;
}

/*
** load history: read history file and load it to a double linked list
*/

void	load_history(t_history **history, t_sh *sh, int fd)
{
	char	*line;
	int		i;

	i = HISTSIZE;
	line = ft_get_next_line(fd);
	while (line && i--)
	{
		if (ft_isprintable(line))
			save_line_history(history, sh, line);
		else
		{
			free(line);
			ft_get_next_line(-503);
			exit_error("Line is not printable", sh);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
}

/*
** init history: open history file, read and load history, close history file
** get HOME path to create there .minishell_history
*/

void	init_history(t_sh *sh, char **ev)
{
	char	*home;
	int		len_home;
	int		fd;

	home = ev[k24("HOME")];
	if (home)
	{
		len_home = ft_strlen(home);
		ft_strcpy(sh->history_path, home);
		ft_strcpy(&sh->history_path[len_home], HISTORY_FILE);
		sh->history_path[len_home + ft_strlen(HISTORY_FILE)] = '\0';
		fd = open(sh->history_path, O_RDONLY);
		if (fd == -1)
			exit_error(strerror(errno), sh);
		load_history(&sh->history, sh, fd);
		close(fd);
	}
	else
		exit_error("HOME environmental variable is not set", sh);
}

/*
** write_history: write line to history file
*/

t_history	write_history(t_history *history, int fd)
{
	char		*line;

	if (!history)
		return (NULL);
	line = write_history(history->next, fd);
	if (line)
		ft_printf_fd(line, fd);
	return (history->line);
}

/*
 ** save history: open history file, write history to it, close history file
 */

void	save_history(t_sh *sh)
{
	int			fd;
	char		*line;

	fd = open(sh->history_path, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		exit_error(strerror(errno), sh);
	line = write_history(sh->history, fd);
	if (line)
		ft_printf_fd(line, fd);
	close(fd);
}
