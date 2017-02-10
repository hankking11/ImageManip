#ifndef RGB_STRUCT
#define RGB_STRUCT

typedef struct pixel
    {
    int red;
    int green;
    int blue;
    } Pixel;

#endif

#ifndef PPM_STRUCT
#define PPM_STRUCT

typedef struct ppm 
    {
    int rows;
    int cols;
    int colors;
    Pixel **pixels;
    } ppmPic;

#endif

ppmPic *
readppmPic(char *file);

void
writeppmPic(ppmPic *a,FILE *fp);

ppmPic *
newppmPic(void);

ppmPic * 
invertppmPic(ppmPic *a);

ppmPic *
swapppmPic(ppmPic *a);

ppmPic *
flipppmPic(ppmPic *a);

ppmPic *
rotateppmPic(ppmPic *a);
