#include "stego.h"
#include <stdint.h>
#include <string.h>

int check_file_format(FILE *bmp_input, size_t *image_size, size_t *offset) {
    // Magic Numbers Check
    int c = fgetc(bmp_input);
    if (c != 'B') {
        return 1;
    }

    c = fgetc(bmp_input);
    if (c != 'M') {
        return 1;
    }

    // Image Size Retrieval
    for (int i = 0; i < 24; i += 8) {
        c = fgetc(bmp_input);
        *image_size += c << i;
    }

    fseek(bmp_input, 10, SEEK_SET); // Skip to offset of the image

    for (int i = 0; i < 24; i += 8) {
        c = fgetc(bmp_input);
        *offset += c << i;
    }

    if (*offset != 54) {
        return 1;
    }

    fseek(bmp_input, 28, SEEK_SET); // Skip to color depth

    size_t color_depth = 0;
    for (int i = 0; i < 8; i += 8) {
        c = fgetc(bmp_input);
        color_depth += c << i;
    }

    if (color_depth != 24) {
        return 1;
    }

    return 0;
}

int stego(FILE *bmp_input, FILE *bmp_output, size_t message_len, size_t offset, const char *message, FILE *infile) {

    return 0;
}

int encode_file(FILE *bmp_input, FILE *bmp_output, const char *message, FILE *infile) {
    size_t image_size = 0;
    size_t offset = 0; // Address of beginning of the image itself

    if (check_file_format(bmp_input, &image_size, &offset)) {
        fprintf(stderr, "Error: Invalid file format. Input must be a 24-bit BMP image.\n");
        return 1;
    }

    uint32_t message_len = 0;

    if (message != NULL) {
        message_len = strlen(message);
    }
    else {
        uint32_t read_bytes;
        while ((read_bytes = fread(infile, 1, 54, infile)) > 0) {
            message_len += read_bytes;
        }
        rewind(infile);
    }

    if (image_size < (message_len * 8 + 4)) { // + 4 for storing message_len in 4 bytes
        fprintf(stderr, "Error: Error Message too long for the provided image.\n"
                        "Capacity %lu bytes, Message needed %u bytes.\n", image_size, message_len);
    }

    stego(bmp_input, bmp_output, message_len, offset, message, infile);

    return 0;
}

int decode_file(FILE *bmp_input, FILE *outfile) {
    return 0;
}