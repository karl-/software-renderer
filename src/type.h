#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Color;

#define PINK ((Color) { 255, 0, 255, 255 })
#define COLOR_CHANNEL_COUNT 4

typedef struct
{
	Color* data;
	uint width;
	uint height;
} Image;

static Image CreateImage(uint width, uint height)
{
	Image img;
	img.data = (Color*) malloc(sizeof(Color) * width * height);
	img.width = width;
	img.height = height;
	return img;
}

static void DestroyImage(Image img)
{
	free(img.data);
}
