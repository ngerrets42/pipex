/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:08:55 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 17:41:57 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <unistd.h>
# include <stddef.h>

# define FD_STDIN 0
# define FD_STDOUT 1

int	ft_putstr_fd(const char *str, int fd);
int	str_is_str(const char *str1, const char *str2);
char	*ft_strdup(const char *str);
char	**ft_split(char const *str, char c);

#endif