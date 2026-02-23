#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "argparse.h"
#include "reader.h"
#include "zerocast.h"

#define ZEROCAST_VERSION "0.1.0"

static int path_exists(const char *path) {
    struct stat path_stat;
    return stat(path, &path_stat) == 0;
}

static char *build_default_output_path(const char *input_path) {
    const size_t input_length = strlen(input_path);
    char *output_path = (char *)malloc(input_length + 5);
    if (output_path == NULL) {
        return NULL;
    }

    memcpy(output_path, input_path, input_length);
    memcpy(output_path + input_length, "_out", 5);
    return output_path;
}

static int write_empty_file(const char *output_path) {
    FILE *output_file = fopen(output_path, "wb");
    if (output_file == NULL) {
        fprintf(stderr, "error: failed to create output file: %s\n",
                output_path);
        return 1;
    }

    if (fclose(output_file) != 0) {
        fprintf(stderr, "error: failed to finalize output file: %s\n",
                output_path);
        return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    zerocast_parse_result parse_result;
    char *default_output_path = NULL;
    const char *resolved_output_path = NULL;
    unsigned char *input_data = NULL;
    size_t input_size = 0;
    const zerocast_parse_status parse_status =
        zerocast_parse_args(argc, argv, &parse_result, stderr);

    if (parse_status == ZEROCAST_PARSE_HELP) {
        zerocast_print_usage(stdout, parse_result.program_name);
        return 0;
    }

    if (parse_status == ZEROCAST_PARSE_VERSION) {
        zerocast_print_version(stdout, ZEROCAST_VERSION);
        return 0;
    }

    if (parse_status != ZEROCAST_PARSE_OK) {
        return 1;
    }

    if (parse_result.command_args.output == NULL) {
        default_output_path =
            build_default_output_path(parse_result.command_args.input);
        if (default_output_path == NULL) {
            fprintf(stderr, "error: failed to allocate default output path\n");
            return 1;
        }
        resolved_output_path = default_output_path;
    } else {
        resolved_output_path = parse_result.command_args.output;
    }

    if (path_exists(resolved_output_path)) {
        fprintf(stderr, "error: output already exists: %s\n",
                resolved_output_path);
        free(default_output_path);
        return 1;
    }

    if (zerocast_read_file(parse_result.command_args.input, &input_data,
                                  &input_size, stderr) != 0) {
        free(default_output_path);
        return 1;
    }

    switch (parse_result.command_args.command) {
    case ZEROCAST_COMMAND_COMPRESS: {
        unsigned char *compressed_data = NULL;
        const size_t compressed_size =
            zerocast_compress(input_data, input_size, &compressed_data);
        int write_result;
        (void)compressed_size;
        free(input_data);

        free(compressed_data);
        write_result = write_empty_file(resolved_output_path);
        free(default_output_path);
        return write_result;
    }
    case ZEROCAST_COMMAND_DECOMPRESS: {
        unsigned char *decompressed_data = NULL;
        size_t decompressed_size = 0;
        const int result =
            zerocast_decompress(input_data, input_size, &decompressed_data,
                                &decompressed_size, stderr);
        (void)decompressed_size;
        free(input_data);
        free(decompressed_data);
        free(default_output_path);
        return result;
    }
    default:
        free(input_data);
        free(default_output_path);
        fprintf(stderr, "error: unknown command\n");
        return 1;
    }
}
