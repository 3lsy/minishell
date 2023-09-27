/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:29:03 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/27 19:32:05 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Input redirection: <
** Takes the content of a file and redirects it to the command's STDIN.
** If the file doesn't exist, exit status is 1.
*/