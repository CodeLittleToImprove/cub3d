/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:17:39 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/02/23 18:31:32 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "../libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

char	*get_next_line(int fd);

void	*ft_calloc_complete(size_t count, size_t size);
//char	*ft_strchr(const char *s, int c);
char	*initialize_line_read_if_null(char *line_read);
//size_t	ft_strlen(const char *s);
void	*free_and_return_null(void *ptr);
size_t	find_newline_pos(const char *str);
char	*ft_strjoin_and_free(char *previous_read, char *current_read);
#endif
