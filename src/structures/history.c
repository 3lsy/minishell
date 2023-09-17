/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:35:37 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/17 17:12:24 by echavez-         ###   ########.fr       */
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

void	save_line_history(t_sh *sh, char *line)
{
	t_history	*history_node;

	history_node = create_history_node();
	if (!history_node)
		exit_error(strerror(errno), sh);
	history_node->line = ft_strdup(line);
	if (!history_node->line)
		exit_error(strerror(errno), sh);
	history_node->next = sh->history;
	if (sh->history)
		sh->history->prev = history_node;
	sh->history = history_node;
}

/*
** load history: read history file and load it to a double linked list
*/

void	load_history(t_sh *sh, int fd)
{
	char	*line;
	int		i;

	i = HISTORY_SIZE;
	line = ft_get_next_line(fd);
	while (line && i--)
	{
		if (ft_isprintable(line))
			save_line_history(sh, line);
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
		if (fd != -1)
		{
			load_history(sh, fd);
			close(fd);
		}
	}
}
