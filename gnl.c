#include <stddef.h>
#include <string.h>

#include "gnl.h"

static char	*_get_next_line(int fd, char **s_buf)
{
	int		status;

	if (!s_buf[fd] || !strchr(s_buf[fd], '\n'))
	{
		status = read_and_append(fd, &s_buf[fd]);
		if (status == -1 || // Read error
			(status == 0 && (!s_buf[fd] || *s_buf[fd] == '\0'))) // EOF
		{
			safe_free(&s_buf[fd]);
			return (NULL);
		}
	}

	if (s_buf[fd])
		return (extract_line(&s_buf[fd]));

	return (NULL);
}

static char	*get_next_line_op(gnl_op op, int fd)
{
	static char	*s_buf[BUFFER_COUNT];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	if (op == GNL_GET)
		return (_get_next_line(fd, s_buf));
	else if (op == GNL_CLOSE)
	{
		safe_free(&s_buf[fd]);
		return (NULL);
	}

	return (NULL);
}

char	*get_next_line(int fd)
{
	return (get_next_line_op(GNL_GET, fd));
}

void	close_get_next_line(int fd)
{
	get_next_line_op(GNL_CLOSE, fd);
}
