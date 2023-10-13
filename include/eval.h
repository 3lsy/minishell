/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:47:07 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 15:33:54 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "libraries.h"

/*
** Evaluator
*/

void	ft_evaluator(t_sh *sh);
int		is_builtin(char *cmd);
char	*ft_which(char *cmd, char **ev, char *cmd_path);
void	ft_execute(t_sh *sh, t_ast *cmd);
void	ft_execute_builtin(t_sh *sh, t_ast *cmd);
char	**convert_hashmap_to_ev(t_sh *sh);
void	evaluator_destructor(t_sh *sh);

/*
** Context
*/

void	eval_set_context(t_sh *sh);
void	eval_unset_context(t_sh *sh);

/*
** Builtins
*/

int		ft_exit(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av,
			__attribute__((unused)) char **ev,
			t_sh *sh);
int		ft_echo(int ac, char **av, __attribute__((unused)) char **ev,
			__attribute__((unused)) t_sh *sh);
int		ft_env(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av, char **ev,
			__attribute__((unused)) t_sh *sh);
int		ft_export(int ac, char **av,
			__attribute__((unused)) char **ev, t_sh *sh);
int		ft_pwd(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av,
			__attribute__((unused)) char **ev,
			__attribute__((unused)) t_sh *sh);
int		ft_unset(int ac, char **av, char **ev, t_sh *sh);
int		ft_cd(int ac, char **av, char **ev, t_sh *sh);

/*
** Redirections
*/

int		redirect_io(t_sh *sh, int id, t_ast *cmd);
void	reset_io(t_sh *sh);
int		append_output(char *filename);
int		heredoc(t_sh *sh, char *delimeter, int isbuiltin);
int		input_redirection(t_sh *sh, char *filename, int isbuiltin);
int		output_redirection(char *filename);

#endif
