#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strtok_r(char *str, char *delim, char **saveptr)
{
	char	*token_start;

	if (str)
		*saveptr = str;

	if (!*saveptr)
		return (NULL); // No more tokens left

	while (**saveptr && strchr(delim, **saveptr))
		(*saveptr)++;

	if (!**saveptr) // If we reached the end, return NULL
		return (NULL);

	token_start = *saveptr; // Mark the beginning of the token

	// Find the next delimiter
	while (**saveptr && !strchr(delim, **saveptr))
		(*saveptr)++;

	if (**saveptr)  // If we found a delimiter, replace it with '\0' and advance saveptr
	{
		**saveptr = '\0';
		(*saveptr)++;
	}

	return (token_start);
}

#include <stdio.h>

int main()
{
	char str[] = "F 220                                 d  ,100,0";
	char *saveptr;
	char *token = ft_strtok_r(str, " ,", &saveptr);

	while (token)
	{
		printf("Token: %s\n", token);
		token = ft_strtok_r(NULL, " ,", &saveptr);
	}

	return 0;
}
