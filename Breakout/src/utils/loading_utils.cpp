#include "loading_utils.h"

#if DEBUG
#define Log(x) std::cout << x

#else
#define Log(x) 

#endif

std::string loadFile(const char* file_path)
{
	FILE* file = fopen(file_path, "rt");
	
	if (!file)
	{
		Log("Failed to load the file: ");
		Log(file_path);
		Log("\n");
		return std::string();
	}

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	char* file_data = new char[file_size + 1];
	memset(file_data, 0, file_size + 1);
	fseek(file, 0, SEEK_SET);
	fread(file_data, sizeof(char), file_size, file);
	fclose(file);
	std::string data(file_data);
	delete[] file_data;
	return data;
}

bool loadImage(const char* image_path, unsigned char** image_data, unsigned int* width, unsigned int* height, unsigned int* bits_per_pixel, bool vertical_flip)
{
	FREE_IMAGE_FORMAT format = FIF_UNKNOWN;
	FIBITMAP* image = nullptr;

	format = FreeImage_GetFileType(image_path, 0);
	if (format == FIF_UNKNOWN)
		format = FreeImage_GetFIFFromFilename(image_path);
	if (format == FIF_UNKNOWN)
	{
		Log("Failed to load image: ");
		Log(image_path);
		Log('\n');
		return false;
	}

	if (FreeImage_FIFSupportsReading(format))
		image = FreeImage_Load(format, image_path, 0);
	if (!image)
	{	
		Log("Failed to load image: ");
		Log(image_path);
		Log('\n');
		return false;	
	}

	if (vertical_flip)
		FreeImage_FlipVertical(image);

	*width = FreeImage_GetWidth(image);
	*height = FreeImage_GetHeight(image);
	*bits_per_pixel = FreeImage_GetBPP(image);
	unsigned int image_size = *height * FreeImage_GetPitch(image);
	*image_data = new unsigned char[image_size];
	memcpy(*image_data, FreeImage_GetBits(image), image_size);
	FreeImage_Unload(image);

	return true;
}