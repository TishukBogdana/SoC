#include <stdio.h>
#include "bmp.h"
#include "dsp.h"
#include <math.h>

void getCore(Image src, Pixel * core, int px, int py, int size);


void laplacian(int core [CORE_SIZE * CORE_SIZE] [COLORS], int dst_pix [COLORS]);
Pixel dst_pixel_array[MAX_W * MAX_H];
Pixel src_pixel_array[MAX_W * MAX_H];

void getCore(Image src, Pixel * core, int px, int py, int size) {
    Pixel * ptr = core;
    Pixel val;
    for(int y = py-(size-1)/2; y <= py+(size-1)/2; y++) {
        for(int x = px-(size-1)/2; x <= px+(size-1)/2; x++) {
            if( (y < 0) || (y >= src.height) ||
                (x < 0) || (x >= src.width)) {
                val = src.data[py*src.width + px];
            } else {
                val = src.data[y*src.width + x];
            }
            *ptr++ = val;
        }
    }
}
void assert_equal(Image ref, Image iut){
    for(int y = 0; y < ref.height; y++) {
        for(int x = 0; x < ref.width; x++) {
             int px_index = y*ref.width + x;
             iut.data[px_index].r = iut.data[px_index].r - 256 * ((iut.data[px_index].r & 256) >> 8);
             iut.data[px_index].g = iut.data[px_index].g - 256 * ((iut.data[px_index].g & 256) >> 8);
             iut.data[px_index].b = iut.data[px_index].b - 256 * ((iut.data[px_index].b & 256) >> 8);
             if ((ref.data[px_index].r != iut.data[px_index].r)
                 |(ref.data[px_index].g != iut.data[px_index].g)
                 |(ref.data[px_index].b != iut.data[px_index].b)){
                 printf("image not equal");
                 return;
             }
        }
    }
}
int main(int argc, char *argv[]) {
    
    Image img;
    Image res_img;
    Image ref_img;
    Pixel core  [CORE_SIZE* CORE_SIZE];
    int core_hw [CORE_SIZE * CORE_SIZE][COLORS];
    int pix_dst [COLORS];
    
    img = loadBMP(argv[1]);
    ref_img = loadBMP(argv[2]);
    if(img.data != NULL) {
        printf("The image %s %d x %d px is opened successfully\n", argv[1], img.width, img.height);
    } else {
        printf("Error: The image %s can not be opened\n", argv[1]);
    }

    res_img = img;
    res_img.data = dst_pixel_array;
    
    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.width; x++) {
            getCore(img, core, x, y, CORE_SIZE);
            for ( int  i = 0; i < CORE_SIZE * CORE_SIZE; i++){
                core_hw[i][0] = core[i].r;
                core_hw[i][1] = core[i].g;
                core_hw[i][2] = core[i].b;
            }
            laplacian(core_hw , pix_dst);
            int px_index = y*res_img.width + x;
            res_img.data[px_index].r = img.data[px_index].r + abs(pix_dst[0]);
            res_img.data[px_index].g = img.data[px_index].g + abs(pix_dst[1]);
            res_img.data[px_index].b = img.data[px_index].b + abs(pix_dst[2]);
        }
    }
    
    assert_equal(ref_img, res_img);
    saveBMP("laplacian.bmp", res_img);
   
    return 0;
}
