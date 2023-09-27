/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:33:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/27 19:35:12 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Here document redirection: <<
** Opens a simple prompt to take input from the user, until the user types
** the delimiter. The input is then redirected to the command's STDIN.
*/