#ifndef ZEROCAST_ZEROCAST_H
#define ZEROCAST_ZEROCAST_H

#include <stddef.h>
#include <stdio.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef ZEROCAST_EXPORTS
#define ZEROCAST_API __declspec(dllexport)
#else
#define ZEROCAST_API __declspec(dllimport)
#endif
#else
#define ZEROCAST_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

ZEROCAST_API size_t zerocast_compress(const unsigned char *input_data,
                                      size_t input_size,
                                      unsigned char **out_data);

ZEROCAST_API int zerocast_decompress(const unsigned char *input_data,
                                     size_t input_size,
                                     unsigned char **out_data,
                                     size_t *out_size,
                                     FILE *error_stream);

#ifdef __cplusplus
}
#endif

#endif
