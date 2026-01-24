#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "stego.h"

enum enc_dec{
    ENCODE,
    DECODE
};

void print_usage() {
    printf("Usage:\n");
    printf("  Encoding: ./stego -e -i <bmp_input> -o <outfile> [-f <file> | -m <message>]\n");
    printf("  Decoding: ./stego -d -i <bmp_input> [-x <outfile>]\n");
    printf("  Help:     ./stego -h\n");
}

void print_help() {
    print_usage();
    printf("\nDescription:\n");
    printf("  A steganography tool to hide messages or files within a carrier file.\n\n");

    printf("Options:\n");
    printf("  -e                Operation mode: ENCODE (Hide data).\n");
    printf("  -d                Operation mode: DECODE (Extract data).\n");
    printf("  -i INPUT_FILE     The carrier file to read from (Required).\n");
    printf("  -o OUTPUT_FILE    The resulting file containing hidden data.\n");
    printf("  -f FILE_TO_ENCODE The file to hide inside the carrier file.\n");
    printf("  -m MESSAGE        A string message to hide (Mutually exclusive with -f).\n");
    printf("  -x OUTPUT_FILE    The file where extracted data will be saved (Decoding).\n");
}

int main(int argc, char *argv[]) {
    int opt;
    FILE *bmp_input = NULL;
    FILE *bmp_output = NULL;
    char *message = NULL;
    FILE *infile = NULL;
    FILE *outfile = NULL;
    int enc_dec = -1;
    int error = 0;

    if (argc == 1) {
        print_usage();
        return 1;
    }

    while ((opt = getopt(argc, argv, ":edi:o:m:f:x:h")) != -1) {
        switch (opt) {
            case 'i':
                if (bmp_input != NULL) {
                    fprintf(stderr, "%s: Input file already defined!\n", optarg);
                    print_usage();
                    error++;
                    goto close_files;
                }
                bmp_input = fopen(optarg, "rb");
                if (bmp_input == NULL) {
                    perror(optarg);
                    error++;
                    goto close_files;
                }
                break;
            case 'o':
                if (bmp_output != NULL) {
                    fprintf(stderr, "%s: Output file already defined!\n", optarg);
                    print_usage();
                    error++;
                    goto close_files;
                }
                bmp_output = fopen(optarg, "wb");
                if (bmp_output == NULL) {
                    perror(optarg);
                    error++;
                    goto close_files;
                }
                break;
            case 'm':
                if (message != NULL) {
                    fprintf(stderr, "%s: Message already defined!\n", optarg);
                    print_usage();
                    error++;
                    goto close_files;
                }
                message = strdup(optarg);
                if (message == NULL) {
                    fprintf(stderr, "Message allocation failed!\n");
                    error++;
                    goto close_files;
                }
                break;
            case 'f':
                if (infile != NULL) {
                    fprintf(stderr, "%s: File-to-encode already defined!\n", optarg);
                    print_usage();
                    error++;
                    goto close_files;
                }
                infile = fopen(optarg, "rb");
                if (infile == NULL) {
                    perror(optarg);
                    error++;
                    goto close_files;
                }
                break;
            case 'x':
                if (outfile != NULL) {
                    fprintf(stderr, "%s: Decode-file already defined!\n", optarg);
                    print_usage();
                    error++;
                    goto close_files;
                }
                outfile = fopen(optarg, "wb");
                if (outfile == NULL) {
                    perror(optarg);
                    error++;
                    goto close_files;
                }
                break;
            case 'e':
                if (enc_dec == -1) {
                    enc_dec = ENCODE;
                    break;
                }
                fprintf(stderr, "-%c: Encode/decode flag already set!\n", opt);
                print_usage();
                error++;
                goto close_files;
            case 'd':
                if (enc_dec == -1) {
                    enc_dec = DECODE;
                    break;
                }
                fprintf(stderr, "-%c: Encode/decode flag already set!\n", opt);
                print_usage();
                error++;
                goto close_files;
            case 'h':
                print_help();
                goto close_files;
            case '?':
                fprintf(stderr,"Unrecognised option: -%c\n", optopt);
                print_usage();
                error++;
                goto close_files;
            default:
                break;
        }
    }

    if (bmp_input == NULL) {
        fprintf(stderr, "-i: Input file not defined.\n");
        print_usage();
        error++;
        goto close_files;
    }

    if (message != NULL && infile != NULL) {
        fprintf(stderr, "[-m | -f]: Can pick either message or file, not both!\n");
        print_usage();
        error++;
        goto close_files;
    }

    if (message == NULL && infile == NULL) {
        fprintf(stderr, "[-m | -f]: At least one has to be specified!\n");
        print_usage();
        error++;
        goto close_files;
    }

    if (enc_dec == -1) {
        fprintf(stderr, "[-e | -d]: Operation not specified. Use either -e for encoding or -d for decoding.\n");
        print_usage();
        error++;
        goto close_files;
    }

    if (enc_dec == ENCODE) {
        error = encode_file(bmp_input, outfile, message, infile);
    }
    else {
        error = decode_file(bmp_input, outfile);
    }

close_files:
    if (bmp_input != NULL) {
        fclose(bmp_input);
    }
    if (outfile != NULL) {
        fclose(outfile);
    }
    if (infile != NULL) {
        fclose(infile);
    }
    if (outfile != NULL) {
        fclose(outfile);
    }
    if (message != NULL) {
        free(message);
    }

    if (error != 0) {
        return 1;
    }
    return 0;
}