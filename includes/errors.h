/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:22:06 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 14:43:53 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// source: https://www.adminschoice.com/exit-error-codes-in-bash-and-linux-os

// success
# define EXIT_SUCCES 0
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

#endif