#ifndef ZEROCAST_ARGPARSE_H
#define ZEROCAST_ARGPARSE_H

#include <stdio.h>

typedef enum zerocast_command {
    ZEROCAST_COMMAND_COMPRESS,
    ZEROCAST_COMMAND_DECOMPRESS
} zerocast_command;

typedef enum zerocast_parse_status {
    ZEROCAST_PARSE_OK,
    ZEROCAST_PARSE_HELP,
    ZEROCAST_PARSE_VERSION,
    ZEROCAST_PARSE_ERROR
} zerocast_parse_status;

typedef struct zerocast_cli_args {
    zerocast_command command;
    const char *input;
    const char *output;
} zerocast_cli_args;

typedef struct zerocast_parse_result {
    zerocast_parse_status status;
    const char *program_name;
    zerocast_cli_args command_args;
} zerocast_parse_result;

void zerocast_print_usage(FILE *stream, const char *program_name);

void zerocast_print_version(FILE *stream, const char *version);

zerocast_parse_status zerocast_parse_args(int argc, char **argv,
                                          zerocast_parse_result *out_result,
                                          FILE *error_stream);

#endif
