/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:51 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/07 16:12:12 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "analyzer.h"
# include "eval.h"

# define TRUE 1

/*
** main
*/

t_cmd	*ft_cmd(void);
void	exit_error(char *e);

/*
** structures
*/

t_ast	*new_cmd(char *bin, int ac, char **av);

/*
** signal
*/

void	ft_sigint(int sig);
void	ft_sigquit(int sig);
void	ft_sigtstp(int sig);

#endif
