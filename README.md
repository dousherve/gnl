# gnl (*g*et_*n*ext_*l*ine)

Given a file descriptor `int fd`, call `get_next_line(fd)` to read at most `BUFFER_SIZE` bytes
at a time and return the next line, or the rest of the data, or `NULL` if there was an error or if EOF was reached.  


The returned line is allocated with `malloc`, it is your responsability to `free` it.  


Once you're done reading data, call `close_get_next_line(fd)` if you didn't reach
the end of the file in order to free the eventual remaining static buffers.

## Building

Run `make` to build the static library `libgnl.a`.

## Linking

Don't forget to pass the `-L<gnl_dirpath> -lgnl` flags when linking your executable.
