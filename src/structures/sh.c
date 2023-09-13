/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:07:46 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/13 18:14:53 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*ft_sh(void)
{
	static t_sh	x = {
		.exit_status = 0,
		.ast = NULL,
		.ev = NULL,
		.cui = {
		.line = NULL,
		.line_size = 0,
		.cursor = 0,
		.prompt = {
		.username = {0},
		.hostname = {0},
		.cwd = {0},
		.symbol = '$',
	},
	},
	};

	return (&x);
}