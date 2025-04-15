/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:23:01 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/11 15:38:21 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_read_from_buff(int fd, char *save);
char	*ft_get_line(char *save);
char	*ft_rest_of_line(char *save);
size_t	cstm_strlen(const char *str);
char	*cstm_strchr(const char *str, int c);
char	*cstm_strjoin(char *str1, char *str2);

#endif
