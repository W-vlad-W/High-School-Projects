#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "bmp.h"
#include "transformations.h"

int main(int argc, char *argv[]) {
    char* input_file = NULL;
    char* output_file = NULL;
    char* color_filter = NULL;
    float scale_factor = 1.0;
    uint32_t crop_params[4] = {0};  

    FILE *input = input_file ? fopen(input_file, "rb") : stdin;
    if (!input) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *output = output_file ? fopen(output_file, "wb") : stdout;
    if (!output) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    struct bmp_image* image = NULL;
    image = read_bmp(input);
    if (!image) {
        fprintf(stderr, "Error reading BMP file\n");
        exit(EXIT_FAILURE);
    }
    
    struct bmp_image* result_image = rotate_right(image);
    if (!write_bmp(output, result_image)) {
        fprintf(stderr, "Error writing output BMP file\n");
        exit(EXIT_FAILURE);
    }
    free_bmp_image(result_image);

    result_image = rotate_right(image);
    if (!write_bmp(output, result_image)) {
        fprintf(stderr, "Error writing output BMP file\n");
        exit(EXIT_FAILURE);
    }  
    result_image = rotate_left(image);
    if (!write_bmp(output, result_image)) {
        fprintf(stderr, "Error writing output BMP file\n");
        exit(EXIT_FAILURE);
    }    
    result_image = flip_horizontally(image);
    if (!write_bmp(output, result_image)) {
        fprintf(stderr, "Error writing output BMP file\n");
        exit(EXIT_FAILURE);
    }     
    result_image = flip_vertically(image);
    if (!write_bmp(output, result_image)) {
        fprintf(stderr, "Error writing output BMP file\n");
        exit(EXIT_FAILURE);
    }
    result_image = crop(image, crop_params[0], crop_params[1], crop_params[2], crop_params[3]);
    if (!write_bmp(output, result_image)) {
        fprintf(stderr, "Error writing output BMP file\n");
        exit(EXIT_FAILURE);
    }
    result_image = scale(image, scale_factor);
    if (!write_bmp(output, result_image)) {
        fprintf(stderr, "Error writing output BMP file\n");
        exit(EXIT_FAILURE);
    }     
    result_image = extract(image, color_filter);
    if (!write_bmp(output, result_image)) {
        fprintf(stderr, "Error writing output BMP file\n");
        exit(EXIT_FAILURE);
    }

    free_bmp_image(image);
    free_bmp_image(result_image);

    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);

    return 0;
}