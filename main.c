#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef unsigned int uint;

int main(int argc, char **args)
{
	const int k_Width = 256;
	const int k_Height = 256;
	const int k_Channels = 4; // rgba
	uint size = k_Width * k_Height * k_Channels;
	unsigned char* data = malloc(sizeof(unsigned char) * size);

	for(uint i = 0; i < size; i += k_Channels)
	{
		data[i+0] = 255;
		data[i+1] = 0;
		data[i+2] = 255;
		data[i+3] = 255;
	}

	// int stbi_write_tga(char const *filename, int w, int h, int comp, const void *data);
	int res = stbi_write_tga("test.tga", k_Width, k_Height, k_Channels, data);

	free(data);

	fprintf(stderr, "res %u\n", res);

	return 0;
}
