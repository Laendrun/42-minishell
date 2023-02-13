/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:22:06 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 20:09:38 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// source: https://www.adminschoice.com/exit-error-codes-in-bash-and-linux-os

// success
# define EXIT_SUCCESS 0
// failure, as defined by the program
# define EXIT_FAILURE 1
// command line usage error
# define EXIT_ERROR 2

// catch all error code | errors such as divide by 0 or oper. not permitted.
# define ERR_ALL 1

// misuse of shell builtin
# define ERR_MISUSE 2

// missing execute permission
# define ERR_NOPERM 126

// cmd not found in path or wrong cmd name
# define ERR_NOEXEC 127

// invalid argument to exit
# define ERR_INVEXARG 128

// Script terminated by ctrl-c
# define ERR_SIGTERM 130

// exit status out of range (OutOfRange)
# define ERR_EXITOOR 255

// syntax error
# define ERR_SYNT 258

// malloc error
# define ERR_MALLOC 260

// ----------------------------------------------
// Error messages
// ----------------------------------------------
# define ERR_CD_ARGS "shellusion: cd: Too many arguments"
# define ERR_CD_CD "shellusion: cd: No such file or directory"

# define ERR_ENV_ARGS "shellusion: env: Too many arguments"

# define ERR_LEX_DQUO "shellusion: lexer: Unclosed double quote"
# define ERR_LEX_SQUO "shellusion: lexer: Unclosed single quote"

# define ERR_MALMES "shellusion: memory allocation error"

# define ERR_PIPE "Error creating pipe :"
# define ERR_CLOSE "Close error :"
# define ERR_OPEN "Open error :"
# define ERR_FORK "Fork error : "
# define ERR_DUP2 "Dup2 error : "

#endif