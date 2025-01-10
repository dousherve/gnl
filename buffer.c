#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gnl.h"

int	read_and_append(int fd, char **buffer)
{
	char	tmp_buf[BUFFER_SIZE + 1];
	char	*new_buf;
	ssize_t	bytes_read;
	size_t	len;

	bytes_read = read(fd, tmp_buf, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read); // Return 0 for EOF, -1 for error

	tmp_buf[bytes_read] = '\0';
	len = *buffer ? strlen(*buffer) : 0;

	new_buf = malloc(len + bytes_read + 1);
	if (!new_buf)
	{
		safe_free(buffer);
		return (-1);
	}

	if (*buffer)
	{
		memcpy(new_buf, *buffer, len);
		free(*buffer);
	}
	memcpy(new_buf + len, tmp_buf, bytes_read);
	new_buf[len + bytes_read] = '\0';

	*buffer = new_buf;
	return (1);
}

char	*extract_line(char **buffer)
{
	char	*newline_pos;
	char	*line;
	char	*remaining;
	size_t	line_len;

	newline_pos = strchr(*buffer, '\n');
	if (newline_pos)
		line_len = newline_pos - *buffer + 1;
	else
		line_len = strlen(*buffer);

	line = strndup(*buffer, line_len);
	if (!line)
		return (NULL);

	remaining = newline_pos ? strdup(newline_pos + 1) : NULL;
	safe_free(buffer);
	*buffer = remaining;

	return (line);
}

void	safe_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
