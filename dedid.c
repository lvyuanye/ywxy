#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HDMI_EDID_LEN 256
#define DEBUG_LOG 0

static uint8_t u8Buf[HDMI_EDID_LEN];

int image_size[][3] = {

	//size_long * size_high  size		以后添加尺寸只需修改这一个数组即可
	{28, 18, 133},
	{30, 18, 141},
	{30, 23, 150},
	{33, 21, 154},
	{34, 19, 156},
	{34, 27, 170},
	{38, 21, 173},
	{41, 23, 185},
	{41, 26, 190},
	{44, 25, 200},
	{48, 27, 215},
	{47, 30, 220},
	{51, 29, 230},
	{52, 29, 236},
	{53, 32, 240},
	{58, 35, 260},
	{70, 39, 315},
	{70, 39, 320},
	{81, 45, 365},
	{82, 46, 370},
	{86, 49, 390},
	{89, 50, 400},
	{93, 52, 420},
	{95, 54, 430},
	{102, 57, 460},
	{104, 58, 470},
	{108, 60, 490},
	{110, 62, 500},
	{121, 68, 550,},
	{143, 80, 650,},
	{165, 93, 750,},
	{190, 107, 860,},
	{204, 115, 920,},
	{216, 122, 980,},
	{247, 107, 1050,}
};

typedef struct
{
	char Manufacturer[8];
	char MonitorName[32];
	uint8_t ProductCode[2];
	int Week;
	int Year;
	int image_size_no;
} EDID_Info;

EDID_Info edid_info = {
	.Manufacturer = "KTC",
	.MonitorName = "KtcMonitor",
	.Week = 5,
	.Year = 2020,
	.ProductCode = {65, 0},
	.image_size_no = 30,
};

// 初始化 EDID 文件
int init_edid_bin(const char *pHdmiEdidFile)
{
	FILE *pBinFile = fopen(pHdmiEdidFile, "rb");
	if (pBinFile == NULL)
	{
		perror("Failed to open EDID file");
		return -1;
	}

	memset(u8Buf, 0, HDMI_EDID_LEN);
	size_t szBufLen = fread(u8Buf, 1, HDMI_EDID_LEN, pBinFile);
	fclose(pBinFile);

	if (szBufLen != HDMI_EDID_LEN)
	{
		fprintf(stderr, "Error: EDID file size is not %d bytes\n", HDMI_EDID_LEN);
		return -1;
	}

	return 0;
}

// 重建 EDID 数据
uint8_t *rebuild_edid(void)
{
	uint8_t *newbuf = (uint8_t *)malloc(HDMI_EDID_LEN);
	if (newbuf == NULL)
	{
		perror("Failed to allocate memory");
		return NULL;
	}

	memcpy(newbuf, u8Buf, HDMI_EDID_LEN);

	// 修改 Manufacturer
	newbuf[0x08] = (((edid_info.Manufacturer[0] - 64) << 2) & 0x7C) | (((edid_info.Manufacturer[1] - 64) >> 3) & 0x03);
	newbuf[0x09] = (((edid_info.Manufacturer[1] - 64) << 5) & 0xE0) | ((edid_info.Manufacturer[2] - 64) & 0x1F);

	// 修改 ProductCode
	newbuf[0x0a] = edid_info.ProductCode[0];
	newbuf[0x0b] = edid_info.ProductCode[1];

	// 修改 Year 和 Week
	newbuf[0x10] = (edid_info.Week != 0) ? (edid_info.Week & 0xFF) : ((5 + 1) & 0xFF);
	newbuf[0x11] = (edid_info.Year != 0) ? ((edid_info.Year - 1990) & 0xFF) : ((2020 - 1990) & 0xFF);

	// 修改 Panel Size
	newbuf[0x15] = image_size[edid_info.image_size_no][0];
	newbuf[0x16] = image_size[edid_info.image_size_no][1];

	// 修改 Monitor Name
	for (int i = 0; i < 4; i++)
	{
		if ((newbuf[0x36 + 18 * i] == 0x00) && (newbuf[0x37 + 18 * i] == 0x00))
		{
			if (newbuf[0x39 + 18 * i] == 0xfc)
			{
				uint8_t flag = 1;
				for (int j = 0; j < 13; j++)
				{
					if (flag && (edid_info.MonitorName[j] != '\0'))
					{
						newbuf[0x3b + 18 * i + j] = edid_info.MonitorName[j];
					}
					else
					{
						newbuf[0x3b + 18 * i + j] = (flag == 1) ? 0x0a : 0x20;
						flag = 0;
					}
				}
			}
		}
	}

	// 计算校验和
	uint8_t checksum = 0;
	for (int i = 0; i < 127; i++)
		checksum += newbuf[i];
	newbuf[127] = 256 - checksum;

	checksum = 0;
	for (int i = 128; i < 255; i++)
		checksum += newbuf[i];
	newbuf[255] = 256 - checksum;

	return newbuf;
}

#if DEBUG_LOG
void dumpToScr(uint8_t *newbuf)
{
	int i = 0;
	printf("[DEBUG]dumpToScr <<<<<<<<<<\n");
	for (i = 0; i < HDMI_EDID_LEN; i++)
	{
		if (i % 16 == 0)
		{
			printf("\n\t");
		}
		printf("0x%02X, ", newbuf[i]);
	}
	printf("\n};\n");
}
#endif
// 重新加载 EDID 文件
int reload_edid_bin(const uint8_t *newbuf, const char *pHdmiEdidFile)
{
	FILE *pBinFile = fopen(pHdmiEdidFile, "r+");
	if (pBinFile == NULL)
	{
		perror("Failed to open EDID file for writing");
		return -1;
	}

	size_t szBufLen = fwrite(newbuf, 1, HDMI_EDID_LEN, pBinFile);
	fclose(pBinFile);

	if (szBufLen != HDMI_EDID_LEN)
	{
		fprintf(stderr, "Error: Failed to write EDID file\n");
		return -1;
	}

	return 0;
}

// 打印支持的图像尺寸
void print_image_sizes(void)
{
	int count = sizeof(image_size)/(3*sizeof(int));

	for ( int i = 1;i <= count;i++){
		printf("%d.	IMAGE_SIZE_%d\t\t%dx%d\n", i,image_size[i-1][2],image_size[i-1][0],image_size[i-1][1]);
	}
}

// 主函数
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <input_edid_file1> <input_edid_file2> ...\n", argv[0]);
		return -1;
	}

	char input[7][20];
	printf("-----------------------------\n");
	printf(">>>>>>>> EDID Attribute Modification\n");

	printf("Input EDID Manufacturer (3 capital letters):\n=====> ");
	scanf("%3s", input[0]);

	printf("Input EDID Product Code (4 Hex, no spaces):\n=====> ");
	scanf("%4s", input[1]);

	printf("Input EDID Monitor Name (max 13 characters):\n=====> ");
	scanf(" %13[^\n]", input[2]);

	printf("Input EDID Year:\n=====> ");
	scanf("%4s", input[3]);

	printf("Input EDID Week:\n=====> ");
	scanf("%2s", input[4]);

	printf("Input EDID Panel Size:\n");
	print_image_sizes();
	printf("=====> ");
	scanf("%2s", input[5]);

	// 设置 EDID 信息
	strncpy(edid_info.Manufacturer, input[0], 3);
	strncpy(edid_info.MonitorName, input[2], 13);
	edid_info.Week = atoi(input[4]);
	edid_info.Year = atoi(input[3]);
	edid_info.image_size_no = atoi(input[5]) - 1;

	// 处理 ProductCode
	char pd_buf[5] = {0};
	char pd_half_buf[3] = {0};
	strncpy(pd_half_buf, input[1], 2);
	strncpy(pd_buf, input[1], 4);
	edid_info.ProductCode[0] = strtol(pd_buf + 2, NULL, 16);
	edid_info.ProductCode[1] = strtol(pd_half_buf, NULL, 16);

	printf("\033[7mManufacturer = \t%s\n", edid_info.Manufacturer);
	printf("ProductCode  = \t%#2x%.2x\n", edid_info.ProductCode[1], edid_info.ProductCode[0]);
	printf("MonitorName  = \t%s\n", edid_info.MonitorName);
	printf("Week =         \t%d\n", edid_info.Week);
	printf("Year =         \t%d\n", edid_info.Year);
	printf("PanelSize =    \t%dx%d\n\033[0m", image_size[edid_info.image_size_no][0], image_size[edid_info.image_size_no][1]);

	// 处理每个 EDID 文件
	for (int i = 1; i < argc; i++)
	{
		if (init_edid_bin(argv[i]) != 0)
		{
			fprintf(stderr, "Error: Failed to initialize EDID file %s\n", argv[i]);
			continue;
		}

		uint8_t *newEdid = rebuild_edid();
		if (newEdid == NULL)
		{
			fprintf(stderr, "Error: Failed to rebuild EDID for file %s\n", argv[i]);
			continue;
		}

		if (reload_edid_bin(newEdid, argv[i]) != 0)
		{
			fprintf(stderr, "Error: Failed to reload EDID file %s\n", argv[i]);
		}

#if DEBUG_LOG
		dumpToScr(newEdid);
#endif
		free(newEdid);
	}

	return 0;
}


