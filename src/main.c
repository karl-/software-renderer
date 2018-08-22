#include <stdio.h>
#include "type.h"
#include "drawing.h"

#define CHANNEL_COUNT 4
#define WIDTH 512
#define HEIGHT 512

int main(int argc, char **args)
{
	Image image = Image_Create(WIDTH, HEIGHT);
	FillImage(image, PINK);
	DrawLineAA(image, Color_Create(0, 0, 0, 255), Point_Create(32,32), Point_Create(WIDTH-32, HEIGHT-60));
	WriteImage(image, "bin/test.tga");
	Image_Destroy(image);

	return 0;
}

