#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
// from test/examples
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "Debug.h"
#include "EPD_4in2_V2.h"
#include "EPD_Test.h"
#include <stdlib.h>
#include <unistd.h>

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}

int main()
{
    signal(SIGINT, Handler);
	// EPD_4in2_V2_test();
	EPD_4in2_V2_hello_world();
	return 0;
}