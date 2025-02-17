#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HDMI_EDID_LEN     256
#define DEBUG_LOG         1

static uint8_t u8Buf[HDMI_EDID_LEN];

enum {
    IMAGE_SIZE_133 = 0,
    IMAGE_SIZE_141,
    IMAGE_SIZE_150,
    IMAGE_SIZE_154,
    IMAGE_SIZE_156,
    IMAGE_SIZE_170,
    IMAGE_SIZE_173,
    IMAGE_SIZE_185,
    IMAGE_SIZE_190,
    IMAGE_SIZE_200,
    IMAGE_SIZE_215,
    IMAGE_SIZE_220,
    IMAGE_SIZE_230,
    IMAGE_SIZE_236,
    IMAGE_SIZE_240,
    IMAGE_SIZE_260,
    IMAGE_SIZE_315,
    IMAGE_SIZE_320,
    IMAGE_SIZE_365,
    IMAGE_SIZE_370,
    IMAGE_SIZE_390,
    IMAGE_SIZE_400,
    IMAGE_SIZE_420,
    IMAGE_SIZE_430,
    IMAGE_SIZE_460,
    IMAGE_SIZE_470,
    IMAGE_SIZE_490,
    IMAGE_SIZE_500,
    IMAGE_SIZE_550,
    IMAGE_SIZE_650,
    IMAGE_SIZE_750,
    IMAGE_SIZE_860,
    IMAGE_SIZE_920,
    IMAGE_SIZE_980,
    IMAGE_SIZE_1050,

    IMAGE_SIZE_MAX
} image_st;

uint8_t image_size[36][2] = {

	//IMAGE_SIZE_133
	28,18,
	//IMAGE_SIZE_141
	30,18,
	//IMAGE_SIZE_150
	30,23,
	//IMAGE_SIZE_154
	33,21,
	//IMAGE_SIZE_156
	34,19,
	//IMAGE_SIZE_170
	34,27,
	//IMAGE_SIZE_173
	38,21,
	//IMAGE_SIZE_185
	41,23,
	//IMAGE_SIZE_190
	41,26,
	//IMAGE_SIZE_200
	44,25,
	//IMAGE_SIZE_215
	48,27,
	//IMAGE_SIZE_220
	47,30,
	//IMAGE_SIZE_230
	51,29,
	//IMAGE_SIZE_236
	52,29,
	//IMAGE_SIZE_240
	53,32,
	//IMAGE_SIZE_260
	58,35,
	//IMAGE_SIZE_315
	70,39,
	//IMAGE_SIZE_320
	70,39,
	//IMAGE_SIZE_365
	81,45,
	//IMAGE_SIZE_370
	82,46,
	//IMAGE_SIZE_390
	86,49,
	//IMAGE_SIZE_400
	89,50,
	//IMAGE_SIZE_420
	93,52,
	//IMAGE_SIZE_430
	95,54,
	//IMAGE_SIZE_460
	102,57,
	//IMAGE_SIZE_470
	104,58,
	//IMAGE_SIZE_490
	108,60,
	//IMAGE_SIZE_500
	110,62,
	//IMAGE_SIZE_550,//
	121,68,
	//IMAGE_SIZE_650,//
	143,80,
	//IMAGE_SIZE_750,//
	165,93,
	//IMAGE_SIZE_860,//
	190,107,
	//IMAGE_SIZE_920,//
	204,115,
	//IMAGE_SIZE_980,//
	216,122,
	//IMAGE_SIZE_1050,//
	247,107,
	//IMAGE_SIZE_MAX
	93,52,

};

typedef struct {
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
int init_edid_bin(const char *pHdmiEdidFile) {
    FILE *pBinFile = fopen(pHdmiEdidFile, "rb");
    if (pBinFile == NULL) {
        perror("Failed to open EDID file");
        return -1;
    }

    memset(u8Buf, 0, HDMI_EDID_LEN);
    size_t szBufLen = fread(u8Buf, 1, HDMI_EDID_LEN, pBinFile);
    fclose(pBinFile);

    if (szBufLen != HDMI_EDID_LEN) {
        fprintf(stderr, "Error: EDID file size is not %d bytes\n", HDMI_EDID_LEN);
        return -1;
    }

    return 0;
}

// 重建 EDID 数据
uint8_t* rebuild_edid(void) {
    uint8_t *newbuf = (uint8_t *)malloc(HDMI_EDID_LEN);
    if (newbuf == NULL) {
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
    for (int i = 0; i < 4; i++) {
        if ((newbuf[0x36 + 18 * i] == 0x00) && (newbuf[0x37 + 18 * i] == 0x00)) {
            if (newbuf[0x39 + 18 * i] == 0xfc) {
                uint8_t flag = 1;
                for (int j = 0; j < 13; j++) {
                    if (flag && (edid_info.MonitorName[j] != '\0')) {
                        newbuf[0x3b + 18 * i + j] = edid_info.MonitorName[j];
                    } else {
                        newbuf[0x3b + 18 * i + j] = (flag == 1) ? 0x0a : 0x20;
                        flag = 0;
                    }
                }
            }
        }
    }

    // 计算校验和
    uint8_t checksum = 0;
    for (int i = 0; i < 127; i++) checksum += newbuf[i];
    newbuf[127] = 256 - checksum;

    checksum = 0;
    for (int i = 128; i < 255; i++) checksum += newbuf[i];
    newbuf[255] = 256 - checksum;

    return newbuf;
}

#if DEBUG_LOG 
void dumpToScr(uint8_t *newbuf) {
	int i = 0;
	printf("[DEBUG]dumpToScr <<<<<<<<<<\n");
	for (i = 0; i < HDMI_EDID_LEN; i++) {
		if (i % 16 == 0) {
			printf("\n\t");
		}
		printf("0x%02X, ", newbuf[i]);
	}
	printf("\n};\n");
}
#endif
// 重新加载 EDID 文件
int reload_edid_bin(const uint8_t *newbuf, const char *pHdmiEdidFile) {
    FILE *pBinFile = fopen(pHdmiEdidFile, "r+");
    if (pBinFile == NULL) {
        perror("Failed to open EDID file for writing");
        return -1;
    }

    size_t szBufLen = fwrite(newbuf, 1, HDMI_EDID_LEN, pBinFile);
    fclose(pBinFile);

    if (szBufLen != HDMI_EDID_LEN) {
        fprintf(stderr, "Error: Failed to write EDID file\n");
        return -1;
    }

    return 0;
}

// 打印支持的图像尺寸
void print_image_sizes(void) {
	printf("1.	IMAGE_SIZE_133\n");
	printf("2.	IMAGE_SIZE_141\n");
	printf("3.	IMAGE_SIZE_150\n");
	printf("4.	IMAGE_SIZE_154\n");
	printf("5.	IMAGE_SIZE_156\n");
	printf("6.	IMAGE_SIZE_170\n");
	printf("7.	IMAGE_SIZE_173\n");
	printf("8.	IMAGE_SIZE_185\n");
	printf("9.	IMAGE_SIZE_190\n");
	printf("10.	IMAGE_SIZE_200\n");
	printf("11.	IMAGE_SIZE_215\n");
	printf("12.	IMAGE_SIZE_220\n");
	printf("13.	IMAGE_SIZE_230\n");
	printf("14.	IMAGE_SIZE_236\n");
	printf("15.	IMAGE_SIZE_240\n");
	printf("16.	IMAGE_SIZE_260\n");
	printf("17.	IMAGE_SIZE_315\n");
	printf("18.	IMAGE_SIZE_320\n");
	printf("19.	IMAGE_SIZE_365\n");
	printf("20.	IMAGE_SIZE_370\n");
	printf("21.	IMAGE_SIZE_390\n");
	printf("22.	IMAGE_SIZE_400\n");
	printf("23.	IMAGE_SIZE_420\n");
	printf("24.	IMAGE_SIZE_430\n");
	printf("25.	IMAGE_SIZE_460\n");
	printf("26.	IMAGE_SIZE_470\n");
	printf("27.	IMAGE_SIZE_490\n");
	printf("28.	IMAGE_SIZE_500\n");
	printf("29.	IMAGE_SIZE_550\n");
	printf("30.	IMAGE_SIZE_650\n");
	printf("31.	IMAGE_SIZE_750\n");
	printf("32.	IMAGE_SIZE_860\n");
	printf("33.	IMAGE_SIZE_920\n");
	printf("34.	IMAGE_SIZE_980\n");
	printf("35.	IMAGE_SIZE_1050\n");
	printf("36.	IMAGE_SIZE_1100\n");
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

    printf("[DEBUG] Manufacturer = \t%s\n", edid_info.Manufacturer);
    printf("[DEBUG] ProductCode  = \t%#2x%.2x \n", edid_info.ProductCode[1], edid_info.ProductCode[0]);
    printf("[DEBUG] MonitorName  = \t%s\n", edid_info.MonitorName);
    printf("[DEBUG] Week = \t\t%d\n", edid_info.Week);
    printf("[DEBUG] Year = \t\t%d\n", edid_info.Year);
    printf("[DEBUG] PanelSize = \t%dx%d\n", image_size[edid_info.image_size_no][0], image_size[edid_info.image_size_no][1]);

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