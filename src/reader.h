#ifndef ZEROCAST_READER_H
#define ZEROCAST_READER_H

#include <stddef.h>
#include <stdio.h>

int zerocast_read_file(const char *path, unsigned char **out_data,
                              size_t *out_size, FILE *error_stream);

#endif
