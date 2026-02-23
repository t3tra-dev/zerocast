#include "argparse.h"

#include <stdio.h>
#include <string.h>

static const char *resolve_program_name(char **argv) {
    if (argv == NULL || argv[0] == NULL || argv[0][0] == '\0') {
        return "zerocast";
    }

    return argv[0];
}

static int is_help_flag(const char *token) {
    return token != NULL &&
           (strcmp(token, "-h") == 0 || strcmp(token, "--help") == 0 ||
            strcmp(token, "help") == 0);
}

static int is_version_flag(const char *token) {
    return token != NULL &&
           (strcmp(token, "-v") == 0 || strcmp(token, "--version") == 0 ||
            strcmp(token, "version") == 0);
}

void zerocast_print_usage(FILE *stream, const char *program_name) {
    const char *resolved_program_name =
        (program_name == NULL || program_name[0] == '\0') ? "zerocast"
                                                           : program_name;

    fprintf(stream,
            "\"zerocast\" is a *lossy* compression technology that boasts the "
            "highest compression ratio in history.\n");
    fprintf(stream, "\n");
    fprintf(stream, "usage:\n");
    fprintf(stream, "  %s compress <input> [output]\n", resolved_program_name);
    fprintf(stream, "  %s decompress <input> [output]\n",
            resolved_program_name);
    fprintf(stream, "  %s help\n", resolved_program_name);
    fprintf(stream, "  %s version\n", resolved_program_name);
    fprintf(stream, "  %s -h | --help\n", resolved_program_name);
    fprintf(stream, "  %s -v | --version\n", resolved_program_name);
}

void zerocast_print_version(FILE *stream, const char *version) {
    fprintf(stream, "%s\n", version);
}

zerocast_parse_status zerocast_parse_args(int argc, char **argv,
                                          zerocast_parse_result *out_result,
                                          FILE *error_stream) {
    const char *program_name;

    if (out_result == NULL || error_stream == NULL) {
        return ZEROCAST_PARSE_ERROR;
    }

    program_name = resolve_program_name(argv);
    out_result->program_name = program_name;
    out_result->status = ZEROCAST_PARSE_ERROR;
    out_result->command_args.input = NULL;
    out_result->command_args.output = NULL;

    if (argc == 1) {
        out_result->status = ZEROCAST_PARSE_HELP;
        return out_result->status;
    }

    if (is_help_flag(argv[1])) {
        if (argc != 2) {
            fprintf(error_stream, "error: help flag does not accept additional arguments\n");
            zerocast_print_usage(error_stream, program_name);
            return ZEROCAST_PARSE_ERROR;
        }
        out_result->status = ZEROCAST_PARSE_HELP;
        return out_result->status;
    }

    if (is_version_flag(argv[1])) {
        if (argc != 2) {
            fprintf(error_stream,
                    "error: version flag does not accept additional arguments\n");
            zerocast_print_usage(error_stream, program_name);
            return ZEROCAST_PARSE_ERROR;
        }
        out_result->status = ZEROCAST_PARSE_VERSION;
        return out_result->status;
    }

    if (argc != 3 && argc != 4) {
        fprintf(error_stream,
                "error: invalid argument count for command \"%s\"\n", argv[1]);
        zerocast_print_usage(error_stream, program_name);
        return ZEROCAST_PARSE_ERROR;
    }

    if (strcmp(argv[1], "compress") == 0) {
        out_result->command_args.command = ZEROCAST_COMMAND_COMPRESS;
    } else if (strcmp(argv[1], "decompress") == 0) {
        out_result->command_args.command = ZEROCAST_COMMAND_DECOMPRESS;
    } else {
        fprintf(error_stream, "error: unknown command: %s\n", argv[1]);
        zerocast_print_usage(error_stream, program_name);
        return ZEROCAST_PARSE_ERROR;
    }

    out_result->command_args.input = argv[2];
    out_result->command_args.output = argc == 4 ? argv[3] : NULL;
    out_result->status = ZEROCAST_PARSE_OK;

    return out_result->status;
}
