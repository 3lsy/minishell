/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:11:08 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/15 14:35:20 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	home_len(char *home)
{
	int	len;

	len = ft_strlen(home);
	while (len > 0 && home[len - 1] == '/')
		len--;
	return (len);
}

void	reduce_path(char *path, char **ev)
{
	char	*home;
	int		len_home;
	int		len_path;

	home = ev[k24("HOME")];
	if (home)
	{
		len_home = home_len(home);
		if (ft_strncmp(path, home, len_home) == 0)
		{
			len_path = ft_strlen(path) - len_home + 1;
			ft_memmove(path, path + len_home - 1,
				ft_strlen(path) - len_home + 1);
			path[0] = '~';
			path[len_path] = '\0';
		}
	}
}

void	init_prompt(t_prompt *prompt, char **ev)
{
	int	fd;

	if (ev[k24("USER")])
		ft_strcpy(prompt->username, ev[k24("USER")]);
	else if (ev[k24("LOGNAME")])
		ft_strcpy(prompt->username, ev[k24("LOGNAME")]);
	fd = open("/etc/hostname", O_RDONLY);
	if (fd != -1)
	{
		read(fd, prompt->hostname, HOST_NAME_MAX);
		prompt->hostname[ft_strlen(prompt->hostname) - 1] = '\0';
		close(fd);
	}
	getcwd(prompt->cwd, PATH_MAX);
	reduce_path(prompt->cwd, ev);
	if (ft_strcmp(prompt->username, "root") == 0)
		prompt->symbol = '#';
}

void	update_prompt(t_prompt *prompt, char **ev)
{
	getcwd(prompt->cwd, PATH_MAX);
	reduce_path(prompt->cwd, ev);
}

void	ft_prompt(t_cui *cui)
{
	t_prompt	prompt;

	prompt = cui->prompt;
	term_set(INVISIBLE_CURSOR, cui->term_buffer);
	ft_printf(PCOLOR1);
	ft_printf("%s", prompt.username);
	if (prompt.hostname[0] && prompt.username[0])
		ft_printf("@");
	ft_printf("%s", prompt.hostname);
	ft_printf(PEND);
	if (prompt.cwd[0] && (prompt.hostname[0] || prompt.username[0]))
		ft_printf(":");
	ft_printf(PCOLOR2);
	ft_printf("%s", prompt.cwd);
	ft_printf(PEND);
	ft_printf("%c ", prompt.symbol);
	term_set(VISIBLE_CURSOR, cui->term_buffer);
}
