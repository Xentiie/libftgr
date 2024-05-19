#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 4096

void lzss_decompress(FILE *input, FILE *output) {
    char window[WINDOW_SIZE] = {0};
    int window_start = 0;

    while (!feof(input)) {
        int flag = fgetc(input);
        if (flag == EOF) break;

        if (flag == 1) {  // Match flag
            int byte1 = fgetc(input);
            if (byte1 == EOF) break;
            int byte2 = fgetc(input);
            if (byte2 == EOF) break;

            int offset = (byte1 << 4) | (byte2 >> 4);
            int length = (byte2 & 0xF) + 3;

            for (int i = 0; i < length; ++i) {
                char c = window[(window_start - offset + i) % WINDOW_SIZE];
                fputc(c, output);
                window[window_start % WINDOW_SIZE] = c;
                window_start++;
            }
        } else {  // Literal flag
            int literal = fgetc(input);
            if (literal == EOF) break;

            fputc(literal, output);
            window[window_start % WINDOW_SIZE] = literal;
            window_start++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }

    lzss_decompress(input, output);

    fclose(input);
    fclose(output);

    return 0;
}
