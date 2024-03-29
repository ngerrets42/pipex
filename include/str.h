/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:08:55 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/08/10 15:18:52 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

int		ft_putstr_fd(const char *str, int fd);
int		str_is_str(const char *str1, const char *str2);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
char	**ft_split(char const *str, char c);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_strjoin_free(char *str1, char *str2);
char	*ft_strnstr(const char *hstk, const char *ndle, size_t len);

#endif