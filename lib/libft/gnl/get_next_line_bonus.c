/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:22:54 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/11 15:36:20 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[10240];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save[fd])
	{
		save[fd] = malloc(1);
		save[fd][0] = '\0';
	}
	save[fd] = ft_read_from_buff(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	save[fd] = ft_rest_of_line(save[fd]);
	return (line);
}

char	*ft_read_from_buff(int fd, char *save)
{
	char	*buffer;
	int		bits_read;

	bits_read = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char *));
	if (!buffer)
		return (NULL);
	while (!cstm_strchr(save, '\n') && bits_read != 0)
	{
		bits_read = read(fd, buffer, BUFFER_SIZE);
		if (bits_read == -1)
		{
			free(save);
			free(buffer);
			return (NULL);
		}
		buffer[bits_read] = '\0';
		save = cstm_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*ft_get_line(char *save)
{
	char	*str;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	str = (char *)malloc(i + 1 * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_rest_of_line(char *save)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = (char *)malloc((cstm_strlen(save) - i + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i++;
	while (save[i])
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	return (str);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("francinette.txt", O_RDONLY);
// 	for (int i = 0; i < 4; ++i)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
// 		free(str);
// 	}
// 	return (0);
// }
