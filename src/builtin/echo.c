/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:34:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/05 15:34:40 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool     echo_help(char *word)
{
        int     i;

        i = 2;
        while (word[i])
        {
                if (word[i] != 'n')
                        return (false);
                i++;
        }
        return (true);
}

int     commande_echo(char **word)
{
        bool    new_line;

        new_line = true;
        if (ft_strncmp(*word, "echo", ft_strlen(*word)) != 0)
                return (EXIT_FAILURE);
        word++;
        while (*word && ft_strncmp(*word, "-n", 2) == 0)
        {
                if (echo_help(*word) == true)
                {
                        new_line = false;
                        word++;
                }
                else
                        break ;
        }
        while (*word)
        {
                write(1, *word, ft_strlen(*word));
                word++;
                if (*word != NULL)
                        write (1, " ", 1);
        }
        if (new_line)
                write(1, "\n", 1);
        return (EXIT_SUCCESS);
}