/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:51 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/17 16:04:23 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "analyzer.h"
# include "eval.h"

/*
** main
*/

void	exit_error(char *e, t_sh *sh);
void	ft_destructor(t_sh *sh);

/*
** interface
*/

void	term_set(char *event);
void	init_termcap(t_sh *sh);
void	init_termios(t_sh *sh);
void	unset_term(t_sh *sh);
void	init_prompt(t_prompt *prompt, char **ev);
void	ft_prompt(t_prompt prompt);
int		ft_readline(t_cui *cui);

/*
** structures
*/

t_ast	*new_cmd(char *bin, int ac, char **av);
t_sh	*ft_sh(void);
void	init_env(t_sh *sh, char **ev);
void	init_history(t_sh *sh, char **ev);
void	save_line_history(t_history **history, t_sh *sh, char *line);

/*
** signal
*/

void	ft_signals(void);
void	ft_sigint(int sig);

#endif
