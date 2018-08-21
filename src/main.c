#include <stdio.h>
#include "type.h"
#include "drawing.h"

#define CHANNEL_COUNT 4
#define WIDTH 256
#define HEIGHT 256

int main(int argc, char **args)
{
	Image image = CreateImage(WIDTH, HEIGHT);
	FillImage(image, PINK);
	DrawLine(image, 0, 0, 50, 50, (Color) {0, 0, 0, 255});
	WriteImage(image, "bin/test.tga");
	DestroyImage(image);

	return 0;
}

