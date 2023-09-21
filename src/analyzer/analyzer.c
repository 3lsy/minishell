/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/21 21:07:53 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_analyzer(t_sh *sh)
{
	char	**line;
	int		i;

	sh->cui.line = insert_spaces(sh->cui.line);
	if (!sh->cui.line)
		exit_error(strerror(errno), sh);
	line = ft_split_args(sh->cui.line);
	if (!line && errno != EINVAL)
		exit_error(strerror(errno), sh);
	else if (!line)
	{
		ft_fprintf(STDERR_FILENO, "minishell: syntax error unclosed quotes\n");
		return ;
	}
	i = 0;
	ft_printf("[");
	while (line[i])
		ft_printf("%s, ", line[i++]);
	ft_printf("]\n");
	ft_free_split(&line);
}
