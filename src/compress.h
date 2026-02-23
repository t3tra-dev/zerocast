#ifndef ZEROCAST_COMPRESS_H
#define ZEROCAST_COMPRESS_H

#include <stddef.h>

size_t zerocast_compress(const unsigned char *input_data, size_t input_size,
                         unsigned char **out_data);

#endif
