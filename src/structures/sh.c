/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dell <dell@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:07:46 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/13 16:21:28 by dell             ###   ########.fr       */
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
		.username = NULL,
		.hostname = NULL,
		.pwd = NULL,
		.symbol = '$',
	},
	},
	};

	return (&x);
}
