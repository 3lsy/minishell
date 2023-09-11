/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:11:08 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/11 18:23:14 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_prompt(t_prompt *prompt, char **ev)
{
    prompt->username = ev[k24("USER")];
    if (!prompt->username)
        prompt->username = ev[k24("LOGNAME")];
    prompt->hostname = ev[k24("HOSTNAME")]; 
    prompt->pwd = ev[k24("PWD")];
    if (!prompt->pwd)
        prompt->pwd = getcwd(NULL, 0);
    prompt->separator = ':';
    if (!prompt->pwd)
        prompt->separator = ' ';
    prompt->symbol = '$';
    if (ft_strcmp(prompt->username, "root") == 0)
        prompt->symbol = '#';
}
