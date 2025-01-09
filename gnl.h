#ifndef GNL_H_
# define GNL_H_

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef BUFFER_COUNT
#  define BUFFER_COUNT 1024
# endif

typedef enum gnl_op
{
	GNL_GET,
	GNL_CLOSE
}	gnl_op;

char		*get_next_line(int fd);
void		close_get_next_line(int fd);

int			read_and_append(int fd, char **buffer);
char		*extract_line(char **buffer);

void		safe_free(char **ptr);

#endif // GNL_H_
