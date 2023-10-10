#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/stif.h"

void stif_block_free(stif_block_t *b) {

    if (b == NULL)
        return;

    // recursive
    stif_block_free(b->next);

    if (b->data != NULL)
        free(b->data);

    free(b);
}

void stif_free(stif_t *s) {
  if ( s != NULL){
    //RGB image
    if (s->rgb_pixels != NULL) {
      free(s->rgb_pixels);
    }
    //Grayscale image
    if (s->grayscale_pixels != NULL) {
      free(s->grayscale_pixels);
    }

    //Free all the data block
    stif_block_free(s->block_head);
    free(s);
  }
}

stif_block_t *read_stif_block(const unsigned char *buffer, size_t buffer_size, size_t *bytes_read) {

    // catch EOB
    if (*bytes_read == buffer_size)
        return NULL;

    if(bytes_read == NULL){
      fprintf(stderr, "bytes_read is NULL\n");
      return NULL;
    }

    // init block
    stif_block_t *res = malloc(sizeof(stif_block_t));
    res->next = NULL;
    res->data = NULL;

    //Malloc fails
    if(res == NULL){
      fprintf(stderr, "read_stif_block : res\n");
      return NULL;
    }

    // check minimal size
    if ( (*bytes_read) + STIF_BLOCK_MIN_SIZE >= buffer_size) {
        fprintf(stderr, "read_stif_block: size error !!! [%ld >= %ld]\n", (*bytes_read) + STIF_BLOCK_MIN_SIZE, buffer_size);
        free(res);
        return NULL;
    }
    // read block type
    res->block_type = buffer[(*bytes_read)++];
    // read size of data for this block
    res->block_size = *((int32_t*) &buffer[*bytes_read]);
    *bytes_read += 4;

    //Check positive size
    if (res->block_size < 0) {
        fprintf(stderr, "read_stif_block: error negative size !!! [%d]\n", res->block_size);
        free(res);
        return NULL;
    }

    // check block type
    if (res->block_type == STIF_BLOCK_TYPE_HEADER) {
        //Block is header size muste be exactly 9
        if (res->block_size != 9) {
            fprintf(stderr, "read_stif_block: wrong block header size !!! [%d]\n",res->block_size);
            free(res);
            return NULL;
        }
    }

    //Data block
    else if (res->block_type == STIF_BLOCK_TYPE_DATA) {
      //Block is data ensure the size of block is not bigger than our buffer_size
        if ( (*bytes_read) + res->block_size > buffer_size) {
            fprintf(stderr, "read_stif_block: wrong size for STIF_BLOCK_TYPE_DATA !!! [%ld >= %ld]\n",*bytes_read + res->block_size, buffer_size);
            free(res);
            return NULL;
        }
    }

    //Unknow type of block
    else {
        fprintf(stderr, "read_stif_block: wrong block_type !!! [%d]\n",res->block_type);
        free(res);
        return NULL;
    }

    // malloc space for data
    res->data = malloc(sizeof(uint8_t) * res->block_size);

    //Malloc for data fails
    if(res->data == NULL){
      fprintf(stderr, "read block : could not allocate memory for data\n");
      free(res);
      return NULL;
    }
    //Fill the data
    memcpy(res->data,&buffer[*bytes_read],res->block_size);
    *bytes_read += res->block_size;
    return res;
}


stif_t *parse_stif(const unsigned char *buffer, size_t buffer_size) {

    stif_t *img = malloc(sizeof(stif_t));
    if(img == NULL){
      fprintf(stderr, "unable to allocate memory for img\n");
      return NULL;
    }
    //Init image
    img->rgb_pixels = NULL;
    img->grayscale_pixels = NULL;
    img->block_head = NULL;

    // check MAGIC
    uint16_t mg = *(uint16_t*) buffer;
    if (mg != STIF_MAGIC) {
        fprintf(stderr, "parse_stif: wrong magic !!! [%d]\n",mg);
        stif_free(img);
        return NULL;
    }

    // init with 2 (pass the magic)
    size_t *bReaded = malloc(sizeof(size_t));
    if(bReaded == NULL){
      fprintf(stderr, "unable to allocate memory for bReaded\n");
      return NULL;
    }
    *bReaded = 2;

    // first block MUST be header
    stif_block_t *blk = read_stif_block(buffer, buffer_size, bReaded);
    if (blk == NULL) {
      fprintf(stderr, "parse_stif: first block is NULL!!! \n");
      stif_free(img);
      free(bReaded);
      return NULL;
    }

    // The block is not an header
    if (blk->block_type != STIF_BLOCK_TYPE_HEADER) {
        fprintf(stderr, "parse_stif: first block isn't block header!!! [%d]\n",blk->block_type);
        stif_free(img);
        free(blk);
        free(bReaded);
        return NULL;
    }
    // Check the width must be positive
    img->header.width = *(int32_t*) blk->data;
    if (img->header.width <= 0) {
        fprintf(stderr, "parse_stif: wrong header.width!!! [%d]\n",img->header.width);
        stif_free(img);
        free(blk);
        free(bReaded);
        return NULL;
    }
    // Check the height must be positive
    img->header.height = *(int32_t*) &blk->data[4];
    if (img->header.height <= 0) {
        fprintf(stderr, "parse_stif: wrong header.height!!! [%d]\n",img->header.height);
        stif_free(img);
        free(blk);
        free(bReaded);
        return NULL;
    }

    // fill & check color type
    img->header.color_type = blk->data[8];
    // The color is grayscale
    if (img->header.color_type == STIF_COLOR_TYPE_GRAYSCALE) {
        img->rgb_pixels = NULL;
        img->grayscale_pixels = malloc(sizeof(pixel_grayscale_t) * (img->header.height * img->header.width));
        //Malloc for grayscale pixels fails
        if(img->grayscale_pixels == NULL){
          fprintf(stderr, "unable to allocate memory for img->grayscale_pixels\n");
          return NULL;
        }
    }
    // The color is RGB
    else if (img->header.color_type == STIF_COLOR_TYPE_RGB) {
        img->grayscale_pixels = NULL;
        img->rgb_pixels = malloc(sizeof(pixel_rgb_t) * (img->header.height * img->header.width));
        //Malloc for RGB pixels fails
        if(img->rgb_pixels == NULL){
          fprintf(stderr, "unable to allocate memory for img->rgb_pixels\n");
          return NULL;
        }
    }

    // Unknow color type
    else {
        fprintf(stderr, "parse_stif: wrong color_type !!! [%d]\n",img->header.color_type);
        stif_free(img);
        free(blk);
        free(bReaded);
        return NULL;
    }

    // init the list
    img->block_head = blk;
    stif_block_t *prev = blk;
    // Index for pixel list
    uint32_t ip = 0;
    // read block by block and fill the list
    while ((blk = read_stif_block(buffer, buffer_size, bReaded)) != NULL) {
        // must be data block img
        if (blk->block_type != STIF_BLOCK_TYPE_DATA) {
            fprintf(stderr, "parse_stif: wrong block type for block list !!! [%d]\n",blk->block_type);
            stif_free(img);
            free(blk);
            free(bReaded);
            return NULL;
        }

        // chain
        prev->next = blk;
        prev = blk;

        // Type of image is grayscale
        if (img->header.color_type == STIF_COLOR_TYPE_GRAYSCALE) {
          //Copy each pixel inside block data to our pixel array
            for (uint32_t i=0; i< (uint32_t)blk->block_size; i++ ) {
              // Ensure we don't have to much pixels in data block than pixels in our array
                if( ip >= (uint32_t)(img->header.height * img->header.width) ) {
                  fprintf(stderr, "GRAYSCALE parse_stif: To much pixels [%d >= %d]\n",ip, (img->header.height * img->header.width));
                  stif_free(img);
                  free(bReaded);
                  return NULL;
                }
                img->grayscale_pixels[ip++] = blk->data[i];
            }
        }
        else {
          // Check if the pixel in the block data is multiple of 3 (Impose that each R,G,B pixels can't be splited beetween different block)
          if( (blk->block_size % 3)!= 0 ){
            fprintf(stderr, "invalid RGB format, the block size data must be a multiple of 3 = %d\n",blk->block_size % 3);
            stif_free(img);
            free(bReaded);
            return NULL;
          }
          //Copy the rgb pixel from block data to our pixel array
            for (int i=0; i<blk->block_size; i+=3 ) {
              // Ensure we don't have to much pixels in data block than pixels in our array
                if( ip >= (uint32_t)(img->header.height * img->header.width)) {
                  fprintf(stderr, "RGB parse_stif: To much pixels [%d >= %d]\n",ip, ((img->header.height * img->header.width)));
                  stif_free(img);
                  free(bReaded);
                  return NULL;
                }
                img->rgb_pixels[ip].red    = blk->data[i];
                img->rgb_pixels[ip].green  = blk->data[i+1];
                img->rgb_pixels[ip++].blue = blk->data[i+2];
            }
        }
    }
//We exit the read of block but some bytes are not readed, error ?
    if((*bReaded) < buffer_size){
        printf("read error; bReaded = %ld\n", *bReaded);
        free(bReaded);
        stif_free(img);
        return NULL;
    }

    free(bReaded);

    return img;
}
