#include "EPD_Test.h"
#include "EPD_4in2_V2.h"
#include <string.h>

int EPD_4in2_V2_partial_refresh(void)
{
	printf("EPD_4IN2_V2_partial_refresh\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_4IN2_V2_Init();
    EPD_4IN2_V2_Clear();
    DEV_Delay_ms(500);

	//Create a new image cache
    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_4IN2_V2_WIDTH % 8 == 0)? (EPD_4IN2_V2_WIDTH / 8 ): (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);

	char str[100];
	for (int i = 0; i < 10; i++)
	{
		fgets(str, sizeof(str), stdin);
		Paint_DrawString_EN(0, i*16, &str, &Font12, WHITE, BLACK);
		EPD_4IN2_V2_PartialDisplay(BlackImage, 0, i*16, EPD_4IN2_V2_WIDTH, 16); // need to figure out what the numbers are here for
		DEV_Delay_ms(500);//Analog clock 1s

	}


	EPD_4IN2_V2_Init();
    EPD_4IN2_V2_Clear();
    printf("Goto Sleep...\r\n");
    EPD_4IN2_V2_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    
    return 0;


}