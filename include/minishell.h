/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:51 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 16:07:08 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "analyzer.h"
# include "eval.h"

/*
** main
*/

void	exit_error(char *e);

/*
** interface
*/

// not interactive
void	notatty(t_sh *sh);

// terminal
void	term_set(char *event, char term_buffer[2048]);
void	init_termcap(t_sh *sh);
void	init_termios(t_sh *sh);
void	unset_term(t_sh *sh);
void	reset_cmdline(t_cui *cui);

void	init_prompt(t_prompt *prompt, char **ev);
void	update_prompt(t_prompt *prompt, char **ev);
void	ft_prompt(t_cui *cui);
void	ft_readline(t_cui *cui, t_sh *sh);

// events
int		delete_key(t_cui *cui, t_sh *sh);
int		left_key(t_cui *cui, t_sh *sh);
int		right_key(t_cui *cui, t_sh *sh);
int		up_key(t_cui *cui, t_sh *sh);
int		down_key(t_cui *cui, t_sh *sh);
void	change_line(t_cui *cui, t_sh *sh, char *line);

/*
** structures
*/

// AST nodes
t_ast	*new_cmd(void);
t_redir	new_redir(char *redir, char *file);

t_sh	*ft_sh(int action);
void	init_env(t_sh *sh, char **ev);
void	init_history(t_sh *sh, char **ev);
void	free_history(t_history **history);
void	save_line_history(t_sh *sh, char *line);
void	ft_destructor(t_sh *sh);
void	save_history(t_sh *sh);
void	free_ev(char **ev);
void	insert_key(char *key, t_sh *sh);
char	*k24_insert(char **ev, char *str);

/*
** signal
*/

void	ft_signals(int setting);
void	ft_sigint(int sig);
void	ft_sigcmd(int sig);
void	ft_signals_exec(void);

#endif
