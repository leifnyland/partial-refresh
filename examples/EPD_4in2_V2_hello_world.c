#include "EPD_Test.h"
#include "EPD_4in2_V2.h"
#include <string.h>

int EPD_4in2_V2_hello_world(void)
{
	printf("hello world test demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }
	printf("Init and Clear\r\n");
    EPD_4IN2_V2_Init();
    EPD_4IN2_V2_Clear();
    DEV_Delay_ms(500);

    // 1. Allocate a buffer for the image
    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_4IN2_V2_WIDTH % 8 == 0)? (EPD_4IN2_V2_WIDTH / 8 ): (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }

    // 2. Tell Paint library about this buffer
	printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
	Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    // 3. Now draw into it
    Paint_DrawString_EN(10, 10, "hello world!", &Font16, WHITE, BLACK);

    // 4. Send buffer to the actual display
    EPD_4IN2_V2_Display(BlackImage);
	DEV_Delay_ms(5000);

	printf("Clearing\r\n");
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