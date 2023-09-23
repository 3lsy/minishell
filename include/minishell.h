/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:51 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/23 19:52:14 by echavez-         ###   ########.fr       */
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

/*
** interface
*/

void	notatty(t_sh *sh);

void	term_set(char *event, char term_buffer[2048]);
void	init_termcap(t_sh *sh);
void	init_termios(t_sh *sh);
void	unset_term(t_sh *sh);
void	reset_cmdline(t_cui *cui);

void	init_prompt(t_prompt *prompt, char **ev);
void	ft_prompt(t_cui *cui);
void	ft_readline(t_cui *cui, t_sh *sh);

int		delete_key(t_cui *cui, t_sh *sh);
int		left_key(t_cui *cui, t_sh *sh);
int		right_key(t_cui *cui, t_sh *sh);
int		up_key(t_cui *cui, t_sh *sh);
int		down_key(t_cui *cui, t_sh *sh);
void	change_line(t_cui *cui, t_sh *sh, char *line);

/*
** Analyzer
*/

void	ft_analyzer(t_sh *sh);
t_byte	is_operator(char *str, int i);
char	**ft_lexer(t_sh *sh);
t_bool	ft_parser(char **tokens);

/*
** Evaluator
*/

void	ft_exit(t_sh *sh);

/*
** structures
*/

t_ast	*new_cmd(char *bin, int ac, char **av);
t_sh	*ft_sh(void);
void	init_env(t_sh *sh, char **ev);
void	init_history(t_sh *sh, char **ev);
void	free_history(t_history **history);
void	save_line_history(t_sh *sh, char *line);
void	ft_destructor(t_sh *sh);
void	save_history(t_sh *sh);
void	free_ev(char **ev);
void	insert_key(char *key, t_sh *sh);

/*
** signal
*/

void	ft_signals(void);
void	ft_sigint(int sig);

#endif
