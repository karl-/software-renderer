#pragma once

#include "type.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static void SetPixel(Image img, Color color, Point point)
{
	img.data[point.y * img.width + point.x] = color;
}

static Color GetPixel(Image img, Point point)
{
	return img.data[point.y * img.width + point.x];
}

static int WriteImage(Image img, const char* path)
{
	return stbi_write_tga(path, img.width, img.height, COLOR_CHANNEL_COUNT, img.data);
}

static void DrawLine(Image img, Color color, Point from, Point to)
{
	uint x0 = from.x;
	uint y0 = from.y;

	uint x1 = to.x;
	uint y1 = to.y;

	for (float t = 0.; t < 1.; t += .01)
	{
		int x = x0 * (1. - t) + x1 * t;
		int y = y0 * (1. - t) + y1 * t;

		SetPixel(img, color, Point_Create(x, y));
	}
}

static void FillImage(Image img, Color color)
{
	for(uint x = 0; x < img.width; x++)
	{
		for(uint y = 0; y < img.height; y++)
		{
			SetPixel(img, color, Point_Create(x, y));
		}
	}
}

static float ipart(float x)
{
    return floor(x);
}

static float fpart(float x)
{
    return x - floor(x);
}

static float rfpart(float x)
{
    return 1. - fpart(x);
}

#define PLOT(x, y, c) SetPixel(img, Color_Lerp(GetPixel(img, Point_Create(x,y)), color, c), Point_Create(x, y))

static void DrawLineAA(Image img, Color color, Point a, Point b)
{
	bool steep = abs(b.y - a.y) > abs(b.x - a.x);

	if (steep)
	{
		a = Point_Swap(a);
		b = Point_Swap(b);
	}

	if (a.x > b.x)
	{
		Point t = Point_Create(a.x, a.y);
		a = b;
		b = t;
	}

	Point d = Point_Create(b.x - a.x, b.y - a.y);
	float gradient = (d.x == 0) ? 1. : (float) d.y / d.x;

	// handle first endpoint
	float xend = roundf(a.x);
	float yend = a.y + gradient * (xend - a.x);
	float xgap = rfpart(a.x + 0.5);
	float xpxl1 = xend; // this will be used in the main loop
	float ypxl1 = ipart(yend);

	if (steep)
	{
		PLOT(ypxl1,   xpxl1, rfpart(yend) * xgap);
		PLOT(ypxl1 + 1, xpxl1,  fpart(yend) * xgap);
	}
	else
	{
		PLOT(xpxl1, ypxl1  , rfpart(yend) * xgap);
		PLOT(xpxl1, ypxl1 + 1,  fpart(yend) * xgap);
	}

	// first y-intersection for the main loop
	float intery = yend + gradient;

	// handle second endpoint
	xend = roundf(b.x);
	yend = b.y + gradient * (xend - b.x);
	xgap = fpart(b.x + 0.5);
	//this will be used in the main loop
	float xpxl2 = xend;
	float ypxl2 = ipart(yend);

	if (steep)
	{
		PLOT(ypxl2  , xpxl2, rfpart(yend) * xgap);
		PLOT(ypxl2 + 1, xpxl2,  fpart(yend) * xgap);
	}
	else
	{
		PLOT(xpxl2, ypxl2,  rfpart(yend) * xgap);
		PLOT(xpxl2, ypxl2 + 1, fpart(yend) * xgap);
	}

	// main loop
	if (steep)
	{
		for (int x = xpxl1 + 1; x < xpxl2 - 1; ++x)
		{
			// for x from xpxl1 + 1 to xpxl2 - 1 do
			PLOT(ipart(intery)  , x, rfpart(intery));
			PLOT(ipart(intery) + 1, x,  fpart(intery));
			intery = intery + gradient;
		}
	}
	else
	{
		for (int x = xpxl1 + 1; x < xpxl2 - 1; ++x)
		{
			// for x from xpxl1 + 1 to xpxl2 - 1 do
			PLOT(x, ipart(intery),  rfpart(intery));
			PLOT(x, ipart(intery) + 1, fpart(intery));
			intery = intery + gradient;
		}
	}
}

#undef PLOT
