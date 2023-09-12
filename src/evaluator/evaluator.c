/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/12 21:50:25 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_evaluator(t_sh *sh)
{
	static char	*av[] = {"/usr/bin/man", "malloc"};

	sh->ast = new_cmd("/usr/bin/man", 2, av);
	if (!sh->ast)
		exit_error(strerror(errno), sh);
	ft_putendl(sh->ast->bin);
}
