#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 4096
#define LOOKAHEAD_BUFFER_SIZE 18

typedef struct {
    int offset;
    int length;
    char next_char;
} LZSSMatch;

LZSSMatch find_longest_match(const char *window, const char *lookahead, int window_size, int lookahead_size) {
    LZSSMatch match = {0, 0, *lookahead};

    for (int i = 0; i < window_size; ++i) {
        int j = 0;
        while (j < lookahead_size && (i + j) < window_size && window[i + j] == lookahead[j]) {
            ++j;
        }
        if (j > match.length) {
            match.length = j;
            match.offset = window_size - i;
            if (j < lookahead_size) {
                match.next_char = lookahead[j];
            }
        }
    }
    return match;
}

void lzss_compress(FILE *input, FILE *output) {
    char window[WINDOW_SIZE] = {0};
    char lookahead[LOOKAHEAD_BUFFER_SIZE] = {0};
    int window_start = WINDOW_SIZE;  // Start with an empty window filled with initial buffer.
    int lookahead_size = 0;
    int bytes_read = 0;

    while ((bytes_read = fread(lookahead + lookahead_size, 1, LOOKAHEAD_BUFFER_SIZE - lookahead_size, input)) > 0) {
        lookahead_size += bytes_read;

        while (lookahead_size > 0) {
            LZSSMatch match = find_longest_match(window, lookahead, window_start, lookahead_size);

            if (match.length > 2) {
                fputc(1, output);  // Flag bit indicating a match
                fputc(match.offset >> 4, output);
                fputc(((match.offset & 0xF) << 4) | (match.length - 3), output);
                if (window_start < WINDOW_SIZE) {
                    memcpy(window + window_start, lookahead, match.length);
                    window_start += match.length;
                } else {
                    memmove(window, window + match.length, WINDOW_SIZE - match.length);
                    memcpy(window + WINDOW_SIZE - match.length, lookahead, match.length);
                }
                lookahead_size -= match.length;
                memmove(lookahead, lookahead + match.length, lookahead_size);
            } else {
                fputc(0, output);  // Flag bit indicating a literal
                fputc(lookahead[0], output);
                if (window_start < WINDOW_SIZE) {
                    window[window_start++] = lookahead[0];
                } else {
                    memmove(window, window + 1, WINDOW_SIZE - 1);
                    window[WINDOW_SIZE - 1] = lookahead[0];
                }
                --lookahead_size;
                memmove(lookahead, lookahead + 1, lookahead_size);
            }
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

    lzss_compress(input, output);

    fclose(input);
    fclose(output);

    return 0;
}
