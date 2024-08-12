/*************************************************************************
	> File Name: ch_bmp.c
	> Author: lvyuanye
	> Mail: lvyy@ktc.cn
	> Created Time: Tue 06 Aug 2024 11:44:04 AM CST
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_COLORS 256

struct bmp_info_header
{
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
} __attribute__((packed));

struct bmp_file_header
{
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
} __attribute__((packed));

typedef struct
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char index; // BMP palette may include an extra reserved byte
} ColorWithIndex;

// 读取24位位深的BMP文件
void read24BitBMP(const char *filename, unsigned char **imageData, int *width, int *height)
{
	FILE *bmpFile = fopen(filename, "rb");
	if (!bmpFile)
	{
		perror("Error: Cannot open the BMP file");
		exit(1);
	}

	struct bmp_file_header fileHeader;
	struct bmp_info_header infoHeader;

	// 读取文件头和信息头
	fread(&fileHeader, sizeof(fileHeader), 1, bmpFile);
	fread(&infoHeader, sizeof(infoHeader), 1, bmpFile);

	if (infoHeader.biBitCount != 24)
	{
		fprintf(stderr, "Error: BMP is not 24-bit.\n");
		exit(1);
	}

	*width = infoHeader.biWidth;
	*height = infoHeader.biHeight;

	// 跳过颜色数据
	fseek(bmpFile, fileHeader.bfOffBits - sizeof(fileHeader) - sizeof(infoHeader), SEEK_CUR);

	// 为图像数据分配内存
	*imageData = (unsigned char *)malloc(*width * *height * 3);
	if (!*imageData)
	{
		perror("Error: Cannot allocate memory for image data");
		exit(1);
	}

	// 读取图像数据
	fread(*imageData, *width * *height * 3, 1, bmpFile);

	fclose(bmpFile);
}

// 写入8位位深的BMP文件
void write8BitBMP(const char *filename, unsigned char *indexedData, int width, int height, unsigned char *palette)
{
	FILE *bmpFile = fopen(filename, "wb");
	if (!bmpFile)
	{
		perror("Error: Cannot open the BMP file for writing");
		exit(1);
	}

	struct bmp_file_header fileHeader;
	struct bmp_info_header infoHeader;
	printf("setting file \n");
	// 设置文件头
	const char bmp_file_type[] = {'B', 'M'};
	fileHeader.bfType = bmp_file_type[0] | (bmp_file_type[1] << 8);
	fileHeader.bfSize = sizeof(fileHeader) + sizeof(infoHeader) + (width * height) + (MAX_COLORS * 4);
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(infoHeader) + (MAX_COLORS * 4);
	printf("setting info \n");
	// 设置信息头
	infoHeader.biSize = sizeof(infoHeader);
	infoHeader.biWidth = width;
	infoHeader.biHeight = height;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 8;
	infoHeader.biCompression = 0;
	infoHeader.biSizeImage = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = MAX_COLORS;
	infoHeader.biClrImportant = MAX_COLORS;
	printf("write setting file begin\n");
	// 写入文件头和信息头
	fwrite(&fileHeader, sizeof(fileHeader), 1, bmpFile);
	fwrite(&infoHeader, sizeof(infoHeader), 1, bmpFile);
	printf("write setting file end\n");

	// 写入调色板
	fwrite(palette, 1, MAX_COLORS * 4, bmpFile);
	printf("write palette end\n");
	// 写入索引图像数据
	fwrite(indexedData, width * height, 1, bmpFile);
	printf("write indexedData end\n");
	fclose(bmpFile);
}

// 将24位颜色数据映射到8位索引数据
void mapColorsToIndices(unsigned char *imageData, ColorWithIndex *palette, unsigned char *indexedData, int width, int height)
{
	int paletteIndex = 0;
	int j = 0;

	for (int i = 0; i < width * height; ++i)
	{
		unsigned char r = imageData[i * 3];
		unsigned char g = imageData[i * 3 + 1];
		unsigned char b = imageData[i * 3 + 2];
		ColorWithIndex searchColor = {r, g, b, 0};

		// 查找调色板中的颜色
		for (j = 0; j < paletteIndex; ++j)
		{
			if (searchColor.red == palette[j].red && searchColor.green == palette[j].green && searchColor.blue == palette[j].blue)
			{
				indexedData[i] = palette[j].index;
				break;
			}
		}

		if (j == paletteIndex && paletteIndex < MAX_COLORS)
		{
			palette[paletteIndex] = (ColorWithIndex){r, g, b, paletteIndex};
			indexedData[i] = paletteIndex;
			++paletteIndex;
		}
	}
}

int main()
{
	const char *inputFilename = "24bit.bmp";
	const char *outputFilename = "8bit.bmp";

	ColorWithIndex *imageData = NULL;
	int width, height;

	// 读取24位位深的BMP图像数据
	printf("begin \n");
	read24BitBMP(inputFilename, &imageData, &width, &height);
	printf("width:%d, height:%d\n", width, height);
	// 分配内存以存储索引数据
	unsigned char *indexedData = (unsigned char *)malloc(width * height * sizeof(unsigned char));
	if (!indexedData)
	{
		free(imageData);
		perror("Error: Cannot allocate memory for indexed data");
		exit(EXIT_FAILURE);
	}
	// 简化的量化逻辑
	ColorWithIndex palette[MAX_COLORS] = {0};
	mapColorsToIndices(imageData, palette, indexedData, width, height);
	// 将24位颜色数据映射到8位索引数据
	// 这里需要实现映射逻辑
	// ...
	printf("write begin\n");
	// 写入8位位深的BMP文件
	write8BitBMP(outputFilename, indexedData, width, height, palette);
	printf("write end\n");
	// 释放内存
	free(imageData);
	free(indexedData);

	printf("Conversion successful.\n");

	return 0;
}

