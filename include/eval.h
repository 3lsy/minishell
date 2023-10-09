/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:47:07 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 13:00:51 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "libraries.h"

/*
** Evaluator
*/

void	ft_evaluator(t_sh *sh);
t_bool	is_builtin(char *cmd);

/*
** Builtins
*/

void	ft_exit(t_sh *sh);

#endif
