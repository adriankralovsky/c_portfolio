#include "stego.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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

int stego(FILE *bmp_input, FILE *bmp_output, uint32_t message_len, size_t offset, const char *message) {
    size_t block_size = 256;
    size_t written_bytes = 0;
    unsigned char *output = malloc(block_size * sizeof(unsigned char));
    if (output == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for output file.\n");
        return 1;
    }

    rewind(bmp_input);

    // Headers
    for (int byte = 0; byte < offset; byte++) {
        const size_t ret_code = fread(&output[written_bytes++],sizeof(unsigned char), 1, bmp_input);
        if (ret_code != 1) {
            if (feof(bmp_input))
                printf("Error reading image file: unexpected end of file\n");
            else if (ferror(bmp_input))
                perror("Error reading image file.");
        }
        if (written_bytes >= block_size) {
            block_size += 256;
            unsigned char *temp = realloc(output, block_size * sizeof(unsigned char));
            if (temp == NULL) {
                fprintf(stderr, "Error: Unable to reallocate memory for output file.\n");
                free(output);
                return 1;
            }
            output = temp;
        }
    }

    // Message Length
    for (int byte = 0; byte < 4; byte++) {
        size_t message_len_byte = 0;
        for (int bit = 0; bit < 8; bit += 8) {
            message_len_byte += message_len << (bit + 8 * byte);
        }
        for (int bit = 0; bit < 8; bit++) {
            int read_byte = 0;
            const size_t ret_code = fread(&read_byte, sizeof(unsigned char), 1, bmp_input);
            if (ret_code != 1) {
                if (feof(bmp_input))
                    printf("Error reading image file: unexpected end of file\n");
                else if (ferror(bmp_input))
                    perror("Error reading image file.");
            }
            read_byte &= 0xFE;
            read_byte += (int)(message_len_byte >> (7 - bit)) & 0x01;
            output[written_bytes++] = (size_t)read_byte;
            if (written_bytes >= block_size) {
                block_size += 256;
                unsigned char *temp = realloc(output, block_size * sizeof(unsigned char));
                if (temp == NULL) {
                    fprintf(stderr, "Error: Unable to reallocate memory for output file.\n");
                    free(output);
                    return 1;
                }
                output = temp;
            }
        }
    }

    // Message
    for (int byte = 0; byte < message_len; byte++) {
        for (int bit = 0; bit < 8; bit++) {
            int read_byte = 0;
            const size_t ret_code = fread(&read_byte, sizeof(unsigned char), 1, bmp_input);
            if (ret_code != 1) {
                if (feof(bmp_input))
                    printf("Error reading image file: unexpected end of file\n");
                else if (ferror(bmp_input))
                    perror("Error reading image file.");
            }
            read_byte &= 0xFE;
            read_byte += (message[byte] >> (7 - bit)) & 0x01;
            output[written_bytes++] = read_byte;
            if (written_bytes >= block_size) {
                block_size += 256;
                unsigned char *temp = realloc(output, block_size * sizeof(unsigned char));
                if (temp == NULL) {
                    fprintf(stderr, "Error: Unable to reallocate memory for output file.\n");
                    free(output);
                    return 1;
                }
                output = temp;
            }
        }
    }

    // Rest of the file
    while (1) {
        if (written_bytes >= block_size) {
            block_size += 256;
            unsigned char *temp = realloc(output, block_size * sizeof(unsigned char));
            if (temp == NULL) {
                fprintf(stderr, "Error: Unable to reallocate memory for output file.\n");
                free(output);
                return 1;
            }
            output = temp;
        }

        size_t ret_code = fread(&output[written_bytes], sizeof(unsigned char), 1, bmp_input);

        if (ret_code != 1) {
            break;
        }

        written_bytes++;
    }

    if (ferror(bmp_input)) {
        perror("Error reading image file.");
    }

    // Output
    if (bmp_output != NULL) {
        fwrite(output, 1, written_bytes, bmp_output);
    } else {
        fwrite(output, 1, written_bytes, stdout);
    }

    free(output);
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
    char *message_to_write = 0;

    if (message != NULL) {
        message_len = strlen(message);
        message_to_write = strdup(message);
    }
    else {
        uint32_t read_bytes = 0;

        char temp_buffer[64];
        while ((read_bytes = fread(temp_buffer, 1, 64, infile)) > 0) {
            message_len += read_bytes;
        }

        rewind(infile);

        message_to_write = malloc(message_len);
        if (message_to_write == NULL) {
            fprintf(stderr, "Error: Unable to allocate memory for file data.\n");
            return 1;
        }

        if (fread(message_to_write, 1, message_len, infile) != message_len) {
            fprintf(stderr, "Error: Failed to read the full content of the secret file.\n");
            free(message_to_write);
            return 1;
        }

        rewind(infile);
    }

    if (image_size < (message_len * 8 + 32)) { // + 32 for storing message_len in 4 bytes, so 32 bits
        fprintf(stderr, "Error: Error Message too long for the provided image.\n"
                        "Capacity %lu bytes, Message needed %u bytes.\n", image_size, message_len);
        free(message_to_write);
        return 1;
    }

    stego(bmp_input, bmp_output, message_len, offset, message_to_write);

    free(message_to_write);
    return 0;
}

int decode_file(FILE *bmp_input, FILE *outfile) {
    size_t image_size = 0;
    size_t offset = 0;

    if (check_file_format(bmp_input, &image_size, &offset)) {
        fprintf(stderr, "Error: Invalid file format. Input must be a 24-bit BMP image.\n");
        return 1;
    }

    return 0;
}