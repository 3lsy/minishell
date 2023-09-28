/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:46:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/28 11:41:57 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYZER_H
# define ANALYZER_H

# include "libraries.h"

/*
** Analyzer
*/

int		ft_analyzer(t_sh *sh);
char	**ft_lexer(t_sh *sh);
t_bool	ft_parser(char **tokens);
void	ft_syntax_tree(t_sh *sh);
void	analyzer_destructor(t_sh *sh);

/*
** Secondary functions
*/

char	***ft_split_cmds(char **tokens);
char	*insert_spaces(char *str);
t_byte	is_operator(char *str, int i);
int		is_redirection(char *token);
t_bool	valid_position(char **tokens, int i);

#endif
