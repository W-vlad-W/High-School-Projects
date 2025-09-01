#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include "transformations.h"

struct bmp_image* flip_horizontally(const struct bmp_image* image) {
    if (image == NULL || image->data  == NULL) return NULL;

    struct bmp_image* result = malloc(sizeof(struct bmp_image));

    result->header = malloc(sizeof(struct bmp_header));

    memcpy(result->header, image->header, sizeof(struct bmp_header));

    uint32_t width = image->header->width;
    uint32_t height = image->header->height;

    result->data = malloc(width * height * sizeof(struct pixel));

    for (uint32_t row = 0; row < height; row++) {
        for (uint32_t col = 0; col < width; col++) {
            result->data[row * width + col] =
                image->data[row * width + (width - col - 1)];
        }
    }

    return result;
}


struct bmp_image* flip_vertically(const struct bmp_image* image){
    if (!image || !image->data) return NULL;

    struct bmp_image* result = malloc(sizeof(struct bmp_image));

    result->header = malloc(sizeof(struct bmp_header));

    memcpy(result->header, image->header, sizeof(struct bmp_header));

    result->data = malloc(image->header->width * image->header->height * sizeof(struct pixel));

    for (uint32_t row = 0; row < image->header->height / 2; row++) {
        for (uint32_t col = 0; col < image->header->width; col++) {
            struct pixel temp = image->data[row * image->header->width + col];
            result->data[row * image->header->width + col] =
                image->data[(image->header->height - row - 1) * image->header->width + col];
            result->data[(image->header->height - row - 1) * image->header->width + col] = temp;
        }
    }

    return result;
}

struct bmp_image* rotate_right(const struct bmp_image* image) {
    if (!image || !image->data) return NULL;

    struct bmp_image* result = malloc(sizeof(struct bmp_image));
    if (!result) return NULL;

    result->header = malloc(sizeof(struct bmp_header));
    if (!result->header) {
        free(result);
        return NULL;
    }

    memcpy(result->header, image->header, sizeof(struct bmp_header));
    uint32_t old_width = image->header->width;
    uint32_t old_height = image->header->height;

    result->header->width = old_height;
    result->header->height = old_width;

    uint32_t new_width = old_height;
    uint32_t new_height = old_width;

    uint32_t bytes_per_pixel = sizeof(struct pixel);
    uint32_t bytes_per_row = new_width * bytes_per_pixel;
    uint32_t padding = (4 - (bytes_per_row % 4)) % 4;
    uint32_t new_row_size = bytes_per_row + padding;
    uint32_t new_image_size = new_row_size * new_height;

    result->header->image_size = new_image_size;
    result->header->size = result->header->offset + new_image_size;

    result->data = malloc(new_width * new_height * sizeof(struct pixel));
    if (!result->data) {
        free(result->header);
        free(result);
        return NULL;
    }

    for (uint32_t row = 0; row < old_height; row++) {
        for (uint32_t col = 0; col < old_width; col++) {
            uint32_t new_row = col;
            uint32_t new_col = new_width - row - 1;
            result->data[new_row * new_width + new_col] = image->data[row * old_width + col];
        }
    }

    return result;
}

struct bmp_image* rotate_left(const struct bmp_image* image) {
    if (!image || !image->data) return NULL;

    struct bmp_image* result = malloc(sizeof(struct bmp_image));
    if (result == NULL) return NULL;

    result->header = malloc(sizeof(struct bmp_header));
    if (result->header == NULL) {
        free(result);
        return NULL;
    }

    memcpy(result->header, image->header, sizeof(struct bmp_header));
    uint32_t old_width = image->header->width;
    uint32_t old_height = image->header->height;

    result->header->width = old_height;
    result->header->height = old_width;

    uint32_t new_width = old_height;
    uint32_t new_height = old_width;

    uint32_t bytes_per_pixel = sizeof(struct pixel);
    uint32_t bytes_per_row = new_width * bytes_per_pixel;
    uint32_t padding = (4 - (bytes_per_row % 4)) % 4;
    uint32_t new_row_size = bytes_per_row + padding;
    uint32_t new_image_size = new_row_size * new_height;

    result->header->image_size = new_image_size;
    result->header->size = result->header->offset + new_image_size;

    result->data = malloc(new_width * new_height * sizeof(struct pixel));
    if (result->data == NULL) {
        free(result->header);
        free(result);
        return NULL;
    }

    for (uint32_t row = 0; row < old_height; row++) {
        for (uint32_t col = 0; col < old_width; col++) {
            uint32_t new_row = col;
            uint32_t new_col = new_width - row - 1;
            result->data[new_row * new_width + new_col] = image->data[row * old_width + col];
        }
    }

    return result;
}


struct bmp_image* scale(const struct bmp_image* image, float factor) {
    if (!image || !image->data || factor <= 0) return NULL;

    uint32_t new_width = (uint32_t)round(image->header->width * factor);
    uint32_t new_height = (uint32_t)round(image->header->height * factor);

    struct bmp_image* result = malloc(sizeof(struct bmp_image));
    if (!result) return NULL;
    
    result->header = malloc(sizeof(struct bmp_header));
    if (!result->header) {
        free(result);
        return NULL;
    }
    
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    result->header->width = new_width;
    result->header->height = new_height;

    uint32_t row_size = ((new_width * 3) + 3) & ~3;
    result->header->image_size = row_size * new_height;
    result->header->size = result->header->offset + result->header->image_size;

    result->data = malloc(new_width * new_height * sizeof(struct pixel));
    if (!result->data) {
        free(result->header);
        free(result);
        return NULL;
    }

    for (uint32_t y = 0; y < new_height; y++) {
        for (uint32_t x = 0; x < new_width; x++) {
            float src_x = x / factor;
            float src_y = y / factor;
            
            uint32_t x1 = (uint32_t)floor(src_x);
            uint32_t y1 = (uint32_t)floor(src_y);
            uint32_t x2 = x1 + 1;
            uint32_t y2 = y1 + 1;
            
            if (x2 >= image->header->width) x2 = image->header->width - 1;
            if (y2 >= image->header->height) y2 = image->header->height - 1;
            
            float x_weight = src_x - x1;
            float y_weight = src_y - y1;
            
            uint32_t orig_height = image->header->height;
            struct pixel p11 = image->data[(orig_height-1-y1) * image->header->width + x1];
            struct pixel p21 = image->data[(orig_height-1-y1) * image->header->width + x2];
            struct pixel p12 = image->data[(orig_height-1-y2) * image->header->width + x1];
            struct pixel p22 = image->data[(orig_height-1-y2) * image->header->width + x2];
            
            result->data[y * new_width + x].blue = (uint8_t)(
                p11.blue * (1-x_weight) * (1-y_weight) +
                p21.blue * x_weight * (1-y_weight) +
                p12.blue * (1-x_weight) * y_weight +
                p22.blue * x_weight * y_weight);
            
            result->data[y * new_width + x].green = (uint8_t)(
                p11.green * (1-x_weight) * (1-y_weight) +
                p21.green * x_weight * (1-y_weight) +
                p12.green * (1-x_weight) * y_weight +
                p22.green * x_weight * y_weight);
            
            result->data[y * new_width + x].red = (uint8_t)(
                p11.red * (1-x_weight) * (1-y_weight) +
                p21.red * x_weight * (1-y_weight) +
                p12.red * (1-x_weight) * y_weight +
                p22.red * x_weight * y_weight);
        }
    }

    return result;
}


struct bmp_image* crop(const struct bmp_image* image,
                      uint32_t start_y,
                      uint32_t start_x,
                      uint32_t height,
                      uint32_t width) {
    if (!image || !image->data || !image->header) return NULL;
    
    if (start_x >= image->header->width ||
        start_y >= image->header->height ||
        start_x + width > image->header->width ||
        start_y + height > image->header->height) {
        return NULL;
    }

    struct bmp_image* cropped = malloc(sizeof(struct bmp_image));
    if (!cropped) return NULL;
    
    cropped->header = malloc(sizeof(struct bmp_header));
    if (!cropped->header) {
        free(cropped);
        return NULL;
    }
    memcpy(cropped->header, image->header, sizeof(struct bmp_header));

    cropped->header->width = width;
    cropped->header->height = height;
    uint32_t new_row_size = ((width * 3) + 3) & ~3; 
    cropped->header->image_size = new_row_size * height;
    cropped->header->size = sizeof(struct bmp_header) + cropped->header->image_size;

    cropped->data = malloc(width * height * sizeof(struct pixel));
    if (!cropped->data) {
        free(cropped->header);
        free(cropped);
        return NULL;
    }

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            uint32_t orig_y = image->header->height - 1 - (start_y + y);
            uint32_t orig_x = start_x + x;
            
            cropped->data[y * width + x] = 
                image->data[orig_y * image->header->width + orig_x];
        }
    }

    return cropped;
}


struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    if (!image || !image->data || !colors_to_keep) {return NULL;}

    bool valid = false;
    for (size_t i = 0; colors_to_keep[i] != '\0'; i++) {
        char c = tolower(colors_to_keep[i]);
        if (c == 'r' || c == 'g' || c == 'b') {
            valid = true;
            break;
        }
    }

    if (!valid) return NULL;

    struct bmp_image* result = malloc(sizeof(struct bmp_image));

    result->header = malloc(sizeof(struct bmp_header));

    memcpy(result->header, image->header, sizeof(struct bmp_header));

    result->header->width = image->header->width;
    result->header->height = image->header->height;

    result->data = malloc(result->header->width * result->header->height * sizeof(struct pixel));

    for (uint32_t row = 0; row < result->header->height; row++) {
        for (uint32_t col = 0; col < result->header->width; col++) {
            struct pixel orig_pixel = image->data[row * image->header->width + col];

            // Start with black
            struct pixel new_pixel = {0, 0, 0};

            for (size_t i = 0; colors_to_keep[i] != '\0'; i++) {
                char color = tolower(colors_to_keep[i]);
                if (color == 'r') new_pixel.red = orig_pixel.red;
                else if (color == 'g') new_pixel.green = orig_pixel.green;
                else if (color == 'b') new_pixel.blue = orig_pixel.blue;
            }

            result->data[row * result->header->width + col] = new_pixel;
        }
    }

    return result;
}
