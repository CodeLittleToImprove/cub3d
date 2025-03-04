#include "../includes/parser.h"

// void	allocate_buffers(char **buffer, char **line, char **last_map_line)
// {
// 	*buffer = malloc(BUFFER_SIZE);
// 	*line = malloc(MAX_LINE);
// 	*last_map_line = malloc(MAX_LINE);
//
// 	if (!(*buffer) || !(*line) || !(*last_map_line))
// 	{
// 		perror("Memory allocation failed");
// 		free(*buffer);
// 		free(*line);
// 		free(*last_map_line);
// 		exit(EXIT_FAILURE);
// 	}
// }
//
// void	free_buffers(char *buffer, char *line, char *last_map_line)
// {
// 	free(buffer);
// 	free(line);
// 	free(last_map_line);
// }