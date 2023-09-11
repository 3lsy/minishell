/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:51 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/11 18:03:09 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "analyzer.h"
# include "eval.h"

# define TRUE 1
# define FALSE 0



/*
** main
*/

t_sh	*ft_sh(void);
void	exit_error(char *e, t_sh *sh);
void    ft_destructor(t_sh *sh);

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
