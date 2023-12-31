# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 11:47:33 by echavez-          #+#    #+#              #
#    Updated: 2023/12/13 21:18:37 by echavez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   minishell                            # Name of the binary

#****************** INC *******************          #
# General
INC         =   ./include/                           # Project header files drectory

# Libft
LIB         =   ./libft/                             # Library to include
LIB_H       =   ./libft/                             # Library header files directory

INCLUDE     =   -O3 -I $(LIB_H) -I $(INC)            # Header files

LIB_INC     =   -L$(LIB_H) -lft -lcurses -lreadline  # Include library

#****************** SRC *******************#

DIRSRC      =   ./src/
DIRAN       :=  $(DIRSRC)/analyzer/
DIREVAL		:=  $(DIRSRC)/evaluator/
DIRINT		:=  $(DIRSRC)/interface/
DIRBLT      :=  $(DIRSRC)/builtin/
DIRSGL      :=  $(DIRSRC)/signal/
DIRSTR      :=  $(DIRSRC)/structures/
DIRRED      :=  $(DIRSRC)/redirections/

DIRS        :=  $(DIRSRC) $(DIRAN) $(DIREVAL) $(DIRINT) $(DIRBLT) $(DIRSGL) $(DIRSTR) $(DIRRED)

SRC         =   main.c debug.c # remove debug.c when done
ANZER       =   analyzer.c lexer.c parser.c syntax_matrix.c syntax_tree.c expand.c analyzer_destructor.c
EVAL        =   evaluator.c execution.c which.c context.c evaluator_destructor.c launcher.c
INTER       =   interface.c prompt.c readline.c events.c skip_events.c notatty.c
BUILT       =   echo.c exit.c pwd.c env.c cd.c export.c unset.c
SIGNL       =   signal.c
STRCT       =   sh.c ast.c ev.c history.c history_file.c destructors.c
REDIR       =   redirect.c input_redirection.c output_redirection.c append_output.c heredoc.c

SRCS        :=  $(SRC) $(ANZER) $(EVAL) $(INTER) $(BUILT) $(SIGNL) $(STRCT) $(REDIR)

#***************** DEPS ******************#

DIROBJ      =   ./depo/

#********************************* END OF CONFIG *********************************#

OAUX        =   $(SRCS:%=$(DIROBJ)%)
DEPS        =   $(OAUX:.c=.d)
OBJS        =   $(OAUX:.c=.o)

.ONESHELL:

$(info Creating directory...)
$(shell mkdir -p $(DIROBJ))

ifdef FLAGS
    ifeq ($(FLAGS), no)
CFLAGS      =
    endif
    ifeq ($(FLAGS), debug)
CFLAGS      =   -Wall -Wextra -Werror -ansi -pedantic -g
    endif
else
CFLAGS      =   -Wall -Wextra -Werror
endif

ifdef VERB
    ifeq ($(VERB), on)
CFLAGS      +=  -DM_VERB
    endif
endif

ifndef VERBOSE
.SILENT:
endif

ENV         =   /usr/bin/env
CC          =   $(ENV) clang
RM          =   $(ENV) rm -rf
ECHO        =   $(ENV) echo -e
MKDIR       =   $(ENV) mkdir -p
GIT         =   $(ENV) git
BOLD        =   "\e[1m"
REVER       =   "\e[7m"
BLINK       =   "\e[5m"
RED         =   "\e[38;2;255;0;0m"
GREEN       =   "\e[92m"
BLUE        =   "\e[34m"
YELLOW      =   "\e[33m"
E0M         =   "\e[0m"

FMT         :=  $(REVER)$(YELLOW)$(BLINK)

#******************************* DEPS COMPILATION ********************************#

define generate_objects
$(DIROBJ)%.o    :   $(1)%.c
	                @printf $(GREEN)"Generating $(NAME) objects... %-33.33s\r"$(E0M) $$@
	                @$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $$@ -c $$<
endef

# Generate objects
$(foreach dir,$(DIRS),$(eval $(call generate_objects,$(dir))))

#******************************* MAIN COMPILATION ********************************#

$(NAME)         :       ftlib $(OBJS)
	                @$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_INC)
	                @$(ECHO)
	                @$(ECHO) '                       '$(FMT)'██████'$(E0M)
	                @$(ECHO) '                   '$(FMT)'████░░░░░░██'$(E0M)
	                @$(ECHO) '                 '$(FMT)'██░░░░░░░░██'$(E0M)
	                @$(ECHO) '               '$(FMT)'██░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '             '$(FMT)'██░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '   '$(FMT)'████████░░░░░░░░░░░░░░░░░░░░░░░░████████'$(E0M)
	                @$(ECHO) ' '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) ' '$(FMT)'██▓▓░░░░░░░░░░░░  ██░░░░  ██░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '   '$(FMT)'██▓▓░░░░░░░░░░████░░░░████░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '     '$(FMT)'██▓▓░░░░░░░░████░░░░████░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░▓▓██░░░░██▓▓░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██▓▓░░░░░░░░░░░░░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██▓▓░░░░░░░░░░░░░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '         '$(FMT)'██░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░██'$(E0M)
	                @$(ECHO) '         '$(FMT)'██▓▓░░▓▓████████████▓▓░░▓▓██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██▓▓██'$(E0M)'            '$(FMT)'██▓▓██'$(E0M)
	                @$(ECHO) '             '$(FMT)'██'$(E0M)'                '$(FMT)'██'$(E0M)
	                @$(ECHO) $(E0M)
	                @$(ECHO) $(BOLD)$(GREEN)'> '$(NAME)' Compiled'$(E0M)

$(OBJS): | mkdepo

clean           :
	                @($(RM) $(OBJS))
	                @($(RM) $(DEPS))
	                @($(RM) $(DIROBJ))
	                @(cd $(LIB) && $(MAKE) clean)
	                @$(ECHO) $(BOLD)$(RED)'> '$(NAME)' directory        cleaned'$(E0M)

all             :       $(NAME)

fclean          :       clean
	                @$(RM) $(NAME)
	                @(cd $(LIB) && $(MAKE) fclean)
	                @$(ECHO) $(BOLD)$(RED)'> Executable             removed'$(E0M)

re              :       fclean mkdepo all

mkdepo			:
					@$(MKDIR) $(DIROBJ)

ftlib           :
	                @(cd $(LIB) && $(MAKE))

init            :
	                @$(GIT) submodule init
	                @$(GIT) submodule update

.PHONY          :       all clean re fclean ftlib mkdepo

-include $(DEPS)
