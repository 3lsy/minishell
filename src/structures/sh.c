/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:07:46 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/12 22:00:23 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*ft_sh(void)
{
	static t_sh	x = {
		.exit_status = 0,
		.line = NULL,
		.ast = NULL,
		.ev = NULL,
		.cui = {
		.prompt = {
		.username = NULL,
		.hostname = NULL,
		.pwd = NULL,
		.symbol = '$',
	},
	},
	};

	return (&x);
}
