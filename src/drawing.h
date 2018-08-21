#pragma once

#include "type.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static void SetPixel(Image img, uint x, uint y, Color color)
{
	img.data[y * img.width + x] = color;
}

static int WriteImage(Image img, const char* path)
{
	return stbi_write_tga(path, img.width, img.height, COLOR_CHANNEL_COUNT, img.data);
}

static void DrawLine(Image img, int x0, int y0, int x1, int y1, Color color)
{
	for (float t = 0.; t < 1.; t += .01)
	{
		int x = x0 * (1. - t) + x1 * t;
		int y = y0 * (1. - t) + y1 * t;

		SetPixel(img, x, y, color);
	}
}

static void FillImage(Image img, Color color)
{
	for(uint x = 0; x < img.width; x++)
	{
		for(uint y = 0; y < img.height; y++)
		{
			SetPixel(img, x, y, color);
		}
	}
}
