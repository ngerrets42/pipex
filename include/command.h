/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 22:32:33 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 23:06:20 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# define FD_IN 0
# define FD_OUT 1

typedef struct s_command
{
	char				**args;
	int					fd[2];
	struct s_command	*next;
}						t_command;

t_command	*command_chain(int argc, char **argv);
void		command_print(t_command *command);

#endif
