#include "dsp.h"
#include <math.h>
void laplacian(int core [CORE_SIZE * CORE_SIZE] [COLORS], int dst_pix [COLORS]) {
    int filt[] = {0, 1, 0,
			      1, -4, 1,
			      0, 1, 0 };
                  
    int res_r = 0;
    int res_g = 0;
    int res_b = 0;

            for(int i = 0; i < CORE_SIZE*CORE_SIZE; i++) {
                res_r += core[i][0] * filt[i];
                res_g += core[i][1] * filt[i];
                res_b += core[i][2] * filt[i];
            }

            if(abs(res_r) > 255) res_r = 255;
            if(abs(res_g) > 255) res_g = 255;
            if(abs(res_b) > 255) res_b = 255;
            dst_pix[0] = res_r;
            dst_pix[1] = res_g;
            dst_pix[2] = res_b;
}

