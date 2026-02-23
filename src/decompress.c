#include "zerocast.h"

int zerocast_decompress(const unsigned char *input_data, size_t input_size,
                        unsigned char **out_data, size_t *out_size,
                        FILE *error_stream) {
    (void)input_data;
    (void)input_size;

    if (out_data != NULL) {
        *out_data = NULL;
    }

    if (out_size != NULL) {
        *out_size = 0;
    }

    fprintf(error_stream, "error: infinite-monkeys has not installed\n");
    return 1;
}
