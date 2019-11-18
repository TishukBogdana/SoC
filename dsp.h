#ifndef _DSP_H
#define _DSP_H

#include "bmp.h"

void getCore(Image src, Pixel * core, int px, int py, int size);


void laplacian(int core [CORE_SIZE * CORE_SIZE] [COLORS], int dst_pix [COLORS]);

#endif // _DSP_H
