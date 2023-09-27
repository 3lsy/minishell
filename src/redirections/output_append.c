/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:32:12 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/27 19:33:23 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Output redirection: >>
** Takes the content of a command's STDOUT and appends it to a file.
** If the file doesn't exist, it is created.
*/