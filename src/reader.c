#include "reader.h"

#include <stdlib.h>

int zerocast_read_file(const char *path, unsigned char **out_data,
                              size_t *out_size, FILE *error_stream) {
    FILE *input_file;
    unsigned char *data;
    long file_size;
    size_t bytes_read;

    if (out_data != NULL) {
        *out_data = NULL;
    }

    if (out_size != NULL) {
        *out_size = 0;
    }

    input_file = fopen(path, "rb");
    if (input_file == NULL) {
        fprintf(error_stream, "error: failed to open input file: %s\n", path);
        return 1;
    }

    if (fseek(input_file, 0, SEEK_END) != 0) {
        fprintf(error_stream, "error: failed to seek input file: %s\n", path);
        fclose(input_file);
        return 1;
    }

    file_size = ftell(input_file);
    if (file_size < 0) {
        fprintf(error_stream,
                "error: failed to determine input file size: %s\n", path);
        fclose(input_file);
        return 1;
    }

    if (fseek(input_file, 0, SEEK_SET) != 0) {
        fprintf(error_stream, "error: failed to seek input file: %s\n", path);
        fclose(input_file);
        return 1;
    }

    data = NULL;
    if (file_size > 0) {
        data = (unsigned char *)malloc((size_t)file_size);
        if (data == NULL) {
            fprintf(error_stream,
                    "error: failed to allocate memory for input file: %s\n",
                    path);
            fclose(input_file);
            return 1;
        }

        bytes_read = fread(data, 1, (size_t)file_size, input_file);
        if (bytes_read != (size_t)file_size) {
            fprintf(error_stream, "error: failed to read input file: %s\n",
                    path);
            free(data);
            fclose(input_file);
            return 1;
        }
    }

    if (fclose(input_file) != 0) {
        fprintf(error_stream, "error: failed to close input file: %s\n", path);
        free(data);
        return 1;
    }

    if (out_data != NULL) {
        *out_data = data;
    } else {
        free(data);
    }

    if (out_size != NULL) {
        *out_size = (size_t)file_size;
    }

    return 0;
}
