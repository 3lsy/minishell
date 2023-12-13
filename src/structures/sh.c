/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smile <smile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:07:46 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/13 17:17:06 by smile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*ft_sh(int action)
{
	static t_sh	x = {
		.cui = {
		.term_buffer = {0},
		.line_size = 0, .cursor = 0, .interactive = 1,
		.history_cursor = NULL, .line = NULL, .tmp_line = NULL,
		.prompt = {
		.symbol = '$',
		.username = {0}, .hostname = {0}, .cwd = {0},
	},
	},
		.cl = {
		.ast = NULL, .tokens = NULL, .cmds = NULL,
		.n_cmds = 0, .exit_status = 0,
		.pipes = NULL, .child_pids = NULL,
	},
		.ec = 0,
		.keys = {NULL}, .history_path = {0},
		.history = NULL, .ev = NULL, .plain_ev = NULL,
	};

	if (action == DESTRUCTOR)
		ft_destructor(&x);
	return (&x);
}
