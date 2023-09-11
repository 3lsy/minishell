/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/11 17:36:11 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_evaluator(t_sh *cmd)
{
	static char	*av[] = {"/usr/bin/man", "malloc"};

	cmd->ast = new_cmd("/usr/bin/man", 2, av);
	if (!cmd->ast)
		exit_error(strerror(errno));
	ft_putendl(cmd->ast->bin);
}
