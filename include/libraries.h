/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libraries.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:00:55 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/13 15:30:04 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARIES_H
# define LIBRARIES_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <termios.h>
# include <errno.h>

# include "libft.h"

# define TRUE 1
# define FALSE 0

/*
*  AST
** - id: {
**     0 : CMD
**     1 : |
**     2 : <
**     3 : >
**     4 : <<
**     5 : >>
**   }
*/

typedef struct s_ast
{
	int				id;
	struct s_ast	*left;
	struct s_ast	*right;

	char			*bin;
	int				ac;
	char			**av;

	char			*file;
}	t_ast;

typedef struct s_prompt
{
	char	*username;
	char	*hostname;
	char	*pwd;
	char	separator;
	char	symbol;
}	t_prompt;

typedef struct s_cui
{
	struct termios	term;
	struct termios	term_backup;
	t_prompt		prompt;
}	t_cui;

/*
** SH
** - line: user input
** - ast: abstract syntax tree
** - ev: environment variables
** - cui: command user interface
** - exit_status: exit status
*/

typedef struct t_sh
{
	char	*line;
	t_ast	*ast;
	char	**ev;
	t_cui	cui;
	int		exit_status;
}	t_sh;

#endif
