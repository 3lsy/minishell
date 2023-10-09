/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:47:07 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 17:40:18 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "libraries.h"

/*
** Evaluator
*/

void	ft_evaluator(t_sh *sh);
t_byte	is_builtin(char *cmd);
char	*ft_which(char *cmd, char **ev, char *cmd_path);
void	ft_execute(t_sh *sh, t_ast *cmd);
void	ft_execute_builtin(t_sh *sh, t_ast *cmd);
char	**convert_hashmap_to_ev(t_sh *sh);

/*
** Builtins
*/

void	ft_exit(t_sh *sh);
int		ft_echo(int ac, char **av, __attribute__((unused)) char **ev);
int		ft_env(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av, char **ev);
int		ft_export(int ac, char **av,
			__attribute__((unused)) char **ev, t_sh *sh);
int		ft_pwd(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av,
			__attribute__((unused)) char **ev);
int		ft_unset(int ac, char **av, char **ev, t_sh *sh);

/*
** Redirections
*/

void	redirect_io(t_sh *sh, int id, t_ast *cmd);
void	reset_io(t_sh *sh);
void	append_output(t_sh *sh, char *filename);
void	heredoc(t_sh *sh, char *delimeter);
void	input_redirection(t_sh *sh, char *filename);
void	output_redirection(t_sh *sh, char *filename);


#endif
