#ifndef ZEROCAST_DECOMPRESS_H
#define ZEROCAST_DECOMPRESS_H

#include <stddef.h>
#include <stdio.h>

int zerocast_decompress(const unsigned char *input_data, size_t input_size,
                        unsigned char **out_data, size_t *out_size,
                        FILE *error_stream);

#endif
