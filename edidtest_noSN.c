#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HDMI_EDID_LEN     256
#define DEBUG_LOG         0

//const char *pHdmiEdidFile = "vendor/common/skg/EDID_BIN/EDID_BIN/port1_14.bin";
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
	IMAGE_SIZE_980,
	IMAGE_SIZE_1050,

	IMAGE_SIZE_MAX
}image_st;

uint8_t image_size[35][2] = {

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
	//IMAGE_SIZE_980,//
	216,122,
	//IMAGE_SIZE_980,//
	247,107,
	//IMAGE_SIZE_MAX
	93,52,

};
typedef struct
{
	char Manufacturer[8];

	char MonitorName[32];
	//int ProductCode;
	uint8_t ProductCode[2];
	//char Product_SN[32];	

	int Week;
	int Year;
	int image_size_no;
	
} EDID_Info;

EDID_Info edid_info = {
	.Manufacturer = "KTC",
	.MonitorName = "KtcMonitor",
	//.Product_SN = "KtcMonitor",
	.Week = 5,
	.Year = 2020,
	.ProductCode = 65,
	.image_size_no = 30,
};

int init_edid_bin(char *pHdmiEdidFile)
{
	FILE *pBinFile = fopen(pHdmiEdidFile, "r");
    if(pBinFile == NULL)
    {
        printf("Failed open: fail\n");              
		return -1;
    }       

	/* reset the buffer */
	memset(u8Buf, 0, HDMI_EDID_LEN);

	/* read the bin file (256 bytes) */
	size_t szBufLen = fread(u8Buf, 1, HDMI_EDID_LEN, pBinFile);
	if(szBufLen != HDMI_EDID_LEN)
	{
		printf("Read an error length in the Bin file!\n");
		fclose(pBinFile);
		return -1;
	}

	/* close the bin file*/
	fclose(pBinFile);

    return 0;
}

uint8_t* rebuild_Edid(void)
{
	uint8_t *newbuf = (uint8_t *) malloc(HDMI_EDID_LEN);
	int i = 0;
	int j = 0;

	memset(newbuf, 0, HDMI_EDID_LEN);

	memcpy(newbuf, u8Buf, HDMI_EDID_LEN);

    // customer
	newbuf[0x08] = (((edid_info.Manufacturer[0] - 64)<<2)&0x7C)|(((edid_info.Manufacturer[1] - 64)>>3)&0x03);
	newbuf[0x09] = (((edid_info.Manufacturer[1] - 64)<<5)&0xE0)|((edid_info.Manufacturer[2] - 64)&0x1F);

	// product
	newbuf[0x0a] = edid_info.ProductCode[0];
	newbuf[0x0b] = edid_info.ProductCode[1];

	// Date
	if(edid_info.Week != 0)
	{
		newbuf[0x10] = edid_info.Week&0xFF;
	}
	else
	{
		newbuf[0x10] = (05 + 1) & 0xFF;
	}

	if(edid_info.Year != 0)
	{
		newbuf[0x11] = (edid_info.Year - 1990)&0xFF;
	}
	else
	{
		newbuf[0x11] = (2020 - 1990) & 0xFF;
	}

	// panel size
	newbuf[0x15] = image_size[edid_info.image_size_no][0];
	newbuf[0x16] = image_size[edid_info.image_size_no][1];

	// product name
	for(i = 0; i < 4; i++)
	// 2	Flag   Flag = 0000h when block used as descriptor 18 bit
	{
		if((newbuf[0x36+18*i] == 0x00)&&(newbuf[0x37+18*i] == 0x00))// is Monitor_Descriptor
		{
			if((newbuf[0x39+18*i]) == 0xfc) //FCh :Monitor name, stored as ASCII, code page # 437
			{
				uint8_t flag = 1;
				for(j = 0;j < 13;j++)//0-12
				{				
					if(flag && (edid_info.MonitorName[j] != '\0'))
					{
						newbuf[0x3b+18*i + j] = edid_info.MonitorName[j];
					}
					else //fill after with 0a 20 20 ....
					{
						if(flag == 1)
						{
							newbuf[0x3b+18*i + j] = 0x0a;
							flag = 0;
						}
						else
						{
							newbuf[0x3b+18*i + j] = 0x20;
						}
					}
				}	
			}
		}
		else//Detailed_Timing_Descriptor
		{
			
		}
	}

	// seriel number
	//for(i = 0; i < 4; i++)
	// 2	Flag   Flag = 0000h when block used as descriptor 18 bit
	/*{
		if((newbuf[0x36+18*i] == 0x00)&&(newbuf[0x37+18*i] == 0x00))// is Monitor_Descriptor
		{
			if((newbuf[0x39+18*i]) == 0xff) //FFh :Monitor SN, stored as ASCII
			{
				uint8_t flag = 1;
				for(j = 0;j < 13;j++)//0-12
				{				
					if(flag && (edid_info.Product_SN[j] != '\0'))
					{
						newbuf[0x3b+18*i + j] = edid_info.Product_SN[j];
					}
					else //fill after with 0a 20 20 ....
					{
						if(flag == 1)
						{
							newbuf[0x3b+18*i + j] = 0x0a;
							flag = 0;
						}
						else
						{
							newbuf[0x3b+18*i + j] = 0x20;
						}
					}
				}	
			}
		}
		else//Detailed_Timing_Descriptor
		{
			
		}
	}*/

	// checksum
	uint8_t Checksum = 0;
	for(i = 0; i < 127; i++)
	{
		Checksum += newbuf[i];
	}
	newbuf[127] = 256 - Checksum;

	Checksum = 0;
	for(i=128;i<255;i++)
	{
		Checksum += newbuf[i];
	}
	newbuf[255] = 256 - Checksum;

	return newbuf;
}

#if DEBUG_LOG 
int dumpToScr(uint8_t *newbuf) {
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

int reload_edid_bin(uint8_t *newbuf,char *pHdmiEdidFile)
{
	uint8_t *reload_buf = (uint8_t *) malloc(HDMI_EDID_LEN);

   	FILE *pBinFile = fopen(pHdmiEdidFile, "w");
    if(pBinFile == NULL)
    {
        printf("Failed open: fail\n");              
		return -1;
    }       

	/* reset the buffer */
	memset(reload_buf, 0, HDMI_EDID_LEN);

	memcpy(reload_buf, newbuf, HDMI_EDID_LEN);

	/* write the bin file (256 bytes) */
	size_t szBufLen = fwrite(reload_buf, 1, HDMI_EDID_LEN, pBinFile);

	if(szBufLen != HDMI_EDID_LEN)
	{
		printf("Write an error length in the Bin file!\n");
		fclose(pBinFile);
		return -1;
	}

	/* close the bin file*/
	fclose(pBinFile);

    return 0;
}

void printf_imagesize(void) 
{
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
	printf("33.	IMAGE_SIZE_980\n");
	printf("34.	IMAGE_SIZE_1050\n");
	printf("35.	IMAGE_SIZE_1100\n");
}

int main(int argc, char **argvv)
{
	char argv[7][20];

	printf("-----------------------------\n");
	printf(">>>>>>>> EDID属性修改\n");
	printf("input EDID Manufacturer(3 capital letter)\n");
	printf("=====>");
	scanf("%s",argv[0]);
	fflush(stdin);

    printf("input EDID Product Code(4 Hex,Don`t support Space key!)\n");
	printf("=====>");
    scanf("%s",argv[1]);
	fflush(stdin);
	getchar();

    printf("input EDID Monitor Name(Max 13 character)\n");
	printf("=====>");
	scanf("%[^\n]",argv[2]);  
	fflush(stdin);
	getchar();

	//printf("input EDID Product seriel number(Max 13 character)\n");
	//printf("=====>");
	//scanf("%[^\n]",argv[6]);  
	//fflush(stdin);
	//getchar();

    printf("input EDID Year:\n");
	printf("=====>");
    scanf("%s",argv[3]);
	fflush(stdin);

    printf("input EDID Week:\n");
	printf("=====>");
    scanf("%s",argv[4]);
	fflush(stdin);

    printf("input EDID u16PanelSize:\n");
	printf_imagesize();
	printf("=====>");
    scanf("%s",argv[5]);
	fflush(stdin);

	#if DEBUG_LOG 
		printf("[DEBUG]scanf Manufacturer %s\n",argv[0]);
		printf("[DEBUG]scanf Productcode %s\n",argv[1]);
		printf("[DEBUG]scanf MonitorName %s\n",argv[2]);
		printf("[DEBUG]scanf Year %s\n",argv[3]);
		printf("[DEBUG]scanf Week %s\n",argv[4]);
		printf("[DEBUG]scanf u16PanelSize %s\n",argv[5]);
		//printf("[DEBUG]scanf product SN %s\n",argv[6]);
	#endif

	char pd_buf[5] = {0},pd_half_buf[3] = {0},tranbuf[10]={0};
	uint8_t midd = 0;
	strcpy(edid_info.Manufacturer, argv[0]);
	strcpy(edid_info.MonitorName, argv[2]);
	//strcpy(edid_info.Product_SN, argv[6]);
	strcpy(pd_buf, argv[1]);
	strncpy(pd_half_buf,pd_buf,2);

	//pd 2 int
	pd_half_buf[2] = '\0';
	//printf("pd_half_buf1:%s src:%s\n",pd_half_buf,pd_buf);
	edid_info.ProductCode[1] = atoi(pd_half_buf);

	memset(pd_half_buf,0,sizeof(pd_half_buf));
	strncpy(pd_half_buf,pd_buf+2,2);
	pd_half_buf[2] = '\0';
	//printf("pd_half_buf2:%s src:%s\n",pd_half_buf,pd_buf);
	edid_info.ProductCode[0] = atoi(pd_half_buf);

	// 2hex
	sprintf(tranbuf,"0x%d",edid_info.ProductCode[0]);
	sscanf(tranbuf,"%x",&midd);
	//printf("trbuf:%s ,0:hex:0x%x -- %d \n",tranbuf,midd,edid_info.ProductCode[0]);
	edid_info.ProductCode[0] = midd;
	memset(tranbuf,0,sizeof(tranbuf));
	sprintf(tranbuf,"0x%d",edid_info.ProductCode[1]);
	sscanf(tranbuf,"%x",&midd);
	//printf("trbuf:%s ,1:hex:0x%x -- %d \n",tranbuf,midd,edid_info.ProductCode[1]);
	edid_info.ProductCode[1] = midd;

	edid_info.Week = atoi(argv[4]);
	edid_info.Year = atoi(argv[3]);
	edid_info.image_size_no = atoi(argv[5]);
	edid_info.image_size_no--;

    #if DEBUG_LOG 
		printf("[DEBUG]Manufacturer = %s\n", edid_info.Manufacturer);
		printf("[DEBUG]MonitorName = %s\n", edid_info.MonitorName);
		printf("[DEBUG]ProductCode = %s  0:%d 1:%d\n",pd_buf, edid_info.ProductCode[0],edid_info.ProductCode[1]);
		printf("[DEBUG]Week = %d\n", edid_info.Week);
		printf("[DEBUG]Year = %d\n", edid_info.Year);
		//printf("[DEBUG]Product_SN = %s\n", edid_info.Product_SN);
    #endif

	char *pHdmiEdidFile = argvv[1];
	//printf("[DEBUG]scanf EDID path %s\n",pHdmiEdidFile);

    init_edid_bin(pHdmiEdidFile);
	uint8_t* Edid = u8Buf;

	#if DEBUG_LOG 
		dumpToScr(Edid);
	#endif

	uint8_t* newEdid1 = rebuild_Edid();

	#if DEBUG_LOG 
		dumpToScr(newEdid1);
	#endif

	reload_edid_bin(newEdid1,pHdmiEdidFile);

	pHdmiEdidFile = argvv[2];

	init_edid_bin(pHdmiEdidFile);
	uint8_t* Edid1 = u8Buf;

	#if DEBUG_LOG 
		dumpToScr(Edid1);
	#endif

	uint8_t* newEdid2 = rebuild_Edid();

	#if DEBUG_LOG 
		dumpToScr(newEdid2);
	#endif

	reload_edid_bin(newEdid2,pHdmiEdidFile);

	pHdmiEdidFile = argvv[3];

	init_edid_bin(pHdmiEdidFile);
	uint8_t* Edid2 = u8Buf;

	#if DEBUG_LOG 
		dumpToScr(Edid2);
	#endif

	uint8_t* newEdid3 = rebuild_Edid();

	#if DEBUG_LOG 
		dumpToScr(newEdid3);
	#endif

	reload_edid_bin(newEdid3,pHdmiEdidFile);

    return 0;
}