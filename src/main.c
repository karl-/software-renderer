#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef unsigned int uint;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} ucolor;

#define PINK (ucolor) { 255, 0, 255, 255}
#define CHANNEL_COUNT 4
#define WIDTH 256
#define HEIGHT 256

void line(int x0, int y0, int x1, int y1, ucolor* img, ucolor clr);

int main(int argc, char **args)
{
	uint size = WIDTH * HEIGHT;
	ucolor* data = (ucolor*) malloc(sizeof(ucolor) * size);

	for(uint i = 0; i < size; i++)
		data[i] = PINK;

	line(0, 0, 50, 50, data, (ucolor) {0, 0, 0, 255});

	int res = stbi_write_tga("bin/test.tga", WIDTH, HEIGHT, CHANNEL_COUNT, data);

	free(data);

	return 0;
}

void line(int x0, int y0, int x1, int y1, ucolor* img, ucolor color)
{
    for (float t=0.; t<1.; t+=.01) {
        int x = x0*(1.-t) + x1*t;
        int y = y0*(1.-t) + y1*t;

        img[y * WIDTH + x] = color;
    }
}
