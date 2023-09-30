/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libraries.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:00:55 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/30 20:59:33 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARIES_H
# define LIBRARIES_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <termios.h>
# include <errno.h>
# include <limits.h>

# include "libft.h"
# include <term.h> 

# define HISTORY_FILE "/.minishell_history"
# define HISTSIZE 1000
# define TRUE 1
# define FALSE 0
# define PCOLOR1 "\e[1;38;2;78;154;6m"
# define PCOLOR2 "\e[1;38;2;52;101;164m"
# define PEND "\e[0m"

/*
** Error messages
*/

# define ERR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define ERR_UNC_QUOTE "minishell: syntax error unclosed quote\n"
# define ERR_TERMIOS "minishell: Could not set the termios attributes.\n"

/*
** Keycodes
*/

# define MAX_CODE_SIZE 6

# define CTRL_D "\x4"
# define DEL "\x7f"
# define LEFT_ARROW "\x1b\x5b\x44"
# define RIGHT_ARROW "\x1b\x5b\x43"
# define UP_ARROW "\x1b\x5b\x41"
# define DOWN_ARROW "\x1b\x5b\x42"

/*
** Terminal Capabilities
*/
# define INVISIBLE_CURSOR "vi"
# define VISIBLE_CURSOR "ve"
# define LEFT_CURSOR "le"
# define RIGHT_CURSOR "nd"
# define CLEAR_RIGHT "ce"
# define STORE_CURSOR "sc"
# define RESTORE_CURSOR "rc"
# define DELETE_CHAR "dc"

/*
** Token types
**
**     0 : CMD
**     1 : |
**     2 : <
**     3 : >
**     4 : <<
**     5 : >>
**
*/

# define CMD 0
# define PIPE 1
# define SGL_L 2
# define SGL_R 3
# define DBL_L 4
# define DBL_R 5

extern t_byte	g_sigint;

/*
** Redirection
** - id: redirection id
**   SGL_L: <
**   SGL_R: >
**   DBL_L: <<
**   DBL_R: >>
** - file: file to redirect
*/

typedef struct s_redir
{
	t_byte	id;
	char	*file;
}	t_redir;

/*
*  AST
** - bin: binary
** - ac: argument count
** - av: argument vector
** - redir: redirections
** - next: next node
*/
typedef struct s_ast
{
	char			*bin;
	int				ac;
	char			**av;
	t_redir			*redir;

	struct s_ast	*next;
}	t_ast;

typedef struct s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;

typedef struct s_prompt
{
	char	username[NAME_MAX + 1];
	char	hostname[HOST_NAME_MAX + 1];
	char	cwd[PATH_MAX + 1];
	char	symbol;
}	t_prompt;

/*
** CUI
** - line: user input
** - line_size: size of user input
** - cursor: position of cursor
** - history_cursor: position of history
** - tmp_line: temporary line
** - term_buffer: terminal buffer for tgetent()
** - term: terminal
** - term_backup: backup of terminal
** - prompt: prompt
*/

typedef struct s_cui
{
	char			*line;
	size_t			line_size;
	size_t			cursor;
	t_history		*history_cursor;
	char			*tmp_line;

	char			term_buffer[2048];
	struct termios	term;
	struct termios	term_backup;
	t_prompt		prompt;
}	t_cui;

typedef struct s_cmds
{
	t_ast		*ast;
	char		**tokens;
	char		***cmds;
	int			n_cmds;
	int			(*pipes)[2];
	pid_t		*child_pids;
	t_byte		exit_status;
}	t_cmds;

/*
** SH
** - line: user input
** - ast: abstract syntax tree
** - ev: environment variables
** - cui: command user interface
** - exit_status: exit status
** - cl: command line
*/

typedef struct t_sh
{
	t_cui		cui;
	t_cmds		cl;
	int			ec;
	char		*keys[K24_SIZE];
	char		**ev;
	t_history	*history;
	char		history_path[PATH_MAX + 1];
}	t_sh;

#endif
