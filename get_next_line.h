//
// get_next_line.h
//

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>

#ifndef GNL_BUFFER_SIZE
# define GNL_BUFFER_SIZE 127
#endif

char	*get_next_line(int fd);

#endif // GET_NEXT_LINE_H
