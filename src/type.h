#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Color;

static Color Color_Create(uint r, uint g, uint b, uint a)
{
	return (Color) { r, g, b, a };
}

#define LERP(x, y, t) (x + (t * (y-x)))

static Color Color_Lerp(Color a, Color b, float t)
{
	return Color_Create(
		LERP(a.r, b.r, t),
		LERP(a.g, b.g, t),
		LERP(a.b, b.b, t),
		LERP(a.a, b.a, t) );
}

#undef LERP

#define PINK Color_Create(255, 0, 255, 255)
#define COLOR_CHANNEL_COUNT 4

typedef struct
{
	int x;
	int y;
} Point;

static Point Point_Create(uint x, uint y)
{
	return (Point) { x, y };
}

static Point Point_Swap(Point point)
{
	return Point_Create(point.y, point.x);
}

typedef struct
{
	Color* data;
	uint width;
	uint height;
} Image;

static Image Image_Create(uint width, uint height)
{
	Image img;
	img.data = (Color*) malloc(sizeof(Color) * width * height);
	img.width = width;
	img.height = height;
	return img;
}

static void Image_Destroy(Image img)
{
	free(img.data);
}
