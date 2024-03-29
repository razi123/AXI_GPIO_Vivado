/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xgpio_l.h"
#include "xparameters.h"
#include "sleep.h"



int main()
{
    XGpio outLed, input;
    int button_data = 0;
    int switch_data = 0;

    XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID);
    XGpio_Initialize(&outLed, XPAR_AXI_GPIO_1_DEVICE_ID);


    XGpio_SetDataDirection(&input, 1, 0xF);
    XGpio_SetDataDirection(&input, 2, 0xF);


    XGpio_SetDataDirection(&outLed, 1,0x0);
    init_platform();
    printf("Hello World\n\r");

    /*
     button_data are the five switch buttons,
     outLed are the 8 LEDs range from 0 to 255, 15 corresponds to 4 leds, 170 corresponds to alternative leds
	 switch value is the DIP switch value range from 0 to 255
      */



    while(1)
    {
    	switch_data = XGpio_DiscreteRead(&input, 2);
    	xil_printf("switch_data = %d \r\n", switch_data);


    	button_data = XGpio_DiscreteRead(&input, 1);

    	if(button_data == 0b00010)
    	{
    		xil_printf("-------ON-----------\r\n");
    		XGpio_DiscreteWrite(&outLed, 1, 170);
    		usleep(2000000);
    	}

    	else
    	{
    		xil_printf("-------OFF-----------\r\n");
    		XGpio_DiscreteWrite(&outLed, 1, 0);
    		usleep(2000000);
    	}

    	usleep(2000000);

  }


    cleanup_platform();
    return 0;
}
