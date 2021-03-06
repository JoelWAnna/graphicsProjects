#ifndef TESTS
#define TESTS
enum {
T_COMP = 1,
T_QUANT_UNIF = 2,
T_FILTBARLET = 4,
T_FILT_BOX = 8,
T_FILT_ENHANCE = 16,
T_FILT_GAUSS_N = 32,
T_FILT_GAUSS = 64,
T_FILT_EDGE = 128,
T_QUANT_POP = 256,
T_DITHER_FS = 512,
T_DITHER_RAND = 1024,
T_DITHER_THRESH = 2048,
T_HALF = 4096,
T_ROTATE = 8192,
T_SCALE = 16134,
T_DOUBLE = 32768,
T_NPR = 65536,
T_GRAY = 131072,
T_DITHER_BRIGHT = 131072<<1,
T_DITHER_CLUST = 131072 <<2


};
void writescript(int x);
const int totest = 
0 /*
| T_COMP
| T_QUANT_UNIF
| T_FILTBARLET
| T_FILT_BOX
| T_FILT_ENHANCE 
| T_FILT_GAUSS_N 
| T_FILT_GAUSS 
| T_FILT_EDGE 
| T_QUANT_POP 
| T_DITHER_FS
| T_DITHER_RAND
| T_DITHER_THRESH
| T_HALF
| T_ROTATE
| T_SCALE
| T_DOUBLE
| T_NPR*/
| T_GRAY
| T_DITHER_BRIGHT
| T_DITHER_CLUST 
;
#endif