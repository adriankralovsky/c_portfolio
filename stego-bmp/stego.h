#ifndef STEGO_STEGO_H
#define STEGO_STEGO_H
#include <stdio.h>

/**
 * @brief Encodes a secret message or file into a carrier file.
 *
 * This function takes a source carrier file (`bmp_input`), hides a payload inside it,
 * and writes the resulting steganographic data to `bmp_output`. The payload can be
 * either a text string (`message`) or the contents of a file (`infile`).
 *
 * @note You must provide either `message` OR `infile`, not both.
 *
 * @param bmp_input   Pointer to the source carrier file (opened in "rb" mode).
 * @param bmp_output  Pointer to the destination file (opened in "wb" mode).
 * @param message  Optional null-terminated string to hide. Pass NULL if using `infile`.
 * @param infile Optional file pointer to the data to hide. Pass NULL if using `message`.
 * * @return 0 on success, or a non-zero error code if the encoding fails
 * (e.g., if the carrier file is too small to hold the payload).
 */
int encode_file(FILE *bmp_input, FILE *bmp_output, const char *message, FILE *infile);

/**
 * @brief Extracts hidden data from a steganographic file.
 *
 * This function analyzes `bmp_input` for hidden content. If a payload is detected,
 * it is extracted and written to `outfile`.
 *
 * @param bmp_input      Pointer to the file containing hidden data (opened in "rb" mode).
 * @param outfile Pointer to the file where extracted data will be written (opened in "wb" mode).
 * * @return 0 on success, or a non-zero error code if no hidden data is found
 * or if extraction fails.
 */
int decode_file(FILE *bmp_input, FILE *outfile);

#endif //STEGO_STEGO_H