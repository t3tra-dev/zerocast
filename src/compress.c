#include "zerocast.h"

size_t zerocast_compress(const unsigned char *input_data, size_t input_size,
                         unsigned char **out_data) {
    (void)input_data;
    (void)input_size;

    if (out_data != NULL) {
        *out_data = NULL;
    }

    return 0;
}
