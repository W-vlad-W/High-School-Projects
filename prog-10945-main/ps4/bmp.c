#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

struct bmp_image* read_bmp(FILE* stream){
    if (!stream) {return NULL;}

    struct bmp_header* header = read_bmp_header(stream);
    if (!header) {
        fprintf(stderr, "Error: This is not a BMP file.\n");
        return NULL;
    }

    struct pixel* data = read_data(stream, header);
    if (!data) {
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        free(header);
        return NULL;
    }

    struct bmp_image* image = calloc(1, sizeof(struct bmp_image));

    image->header = header;
    image->data = data;

    return image;
} 


bool write_bmp(FILE* stream, const struct bmp_image* image) {
    if (!stream || !image) {return false;}

    fwrite(image->header, sizeof(struct bmp_header), 1, stream);

    uint32_t width = image->header->width;
    uint32_t height = image->header->height;
    uint32_t row_size = (width * 3 + 3) & ~3;
    uint8_t padding[3] = {0, 0, 0};

    for (int y = height - 1; y >= 0; y--) {
        fwrite(&image->data[y * width], sizeof(struct pixel), width, stream);
        fwrite(padding, 1, row_size - width * sizeof(struct pixel), stream);
    }

    return true;
} 

struct bmp_header* read_bmp_header(FILE* stream) {
    if (stream == NULL) {
        return NULL;
    }
    
    struct bmp_header* header = (struct bmp_header*) malloc(sizeof(struct bmp_header));
    if (header == NULL) {
        return NULL;
    }
    
    if (fread(header, sizeof(struct bmp_header), 1, stream) != 1) {
        free(header);
        return NULL;
    }

    if (header->type != 0x4D42) {
        free(header);
        return NULL;
    }
    
    return header;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header) {
    if (!stream || !header) return NULL;

    uint32_t width = header->width;
    uint32_t height = header->height;
    
    uint32_t row_size = ((width * 3) + 3) & ~3;

    struct pixel* data = calloc(1, width * height * sizeof(struct pixel));
    if (!data) return NULL;

    if (fseek(stream, header->offset, SEEK_SET) != 0) {
        free(data);
        return NULL;
    }

    for (int y = height - 1; y >= 0; y--) {
        uint8_t* row = malloc(row_size);
        if (!row) {
            free(data);
            return NULL;
        }

        if (fread(row, 1, row_size, stream) != row_size) {
            free(row);
            free(data);
            return NULL;
        }

        for (uint32_t x = 0; x < width; x++) {
            data[y * width + x].blue = row[x * 3];
            data[y * width + x].green = row[x * 3 + 1];
            data[y * width + x].red = row[x * 3 + 2];
        }

        free(row);
    }

    return data;
}

void free_bmp_image(struct bmp_image* image){
    if (image == NULL) {return;}
    free(image->header);
    free(image->data);
    free(image);    
}