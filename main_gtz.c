/*
 *  ======== gtz.c ========
 */    

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "gtz.h"

void clk_SWI_Generate_DTMF(UArg arg0);
void clk_SWI_GTZ_0697Hz(UArg arg0);
void clk_SWI_Find_Result(UArg arg0);


extern void task0_dtmfGen(void);
extern void task1_dtmfDetect(void);

extern char digit;
extern int sample, mag1, mag2, freq1, freq2, gtz_out[8];
extern short coef[8];
/*
 *  ======== main ========
 */
void main(void)
{


	   System_printf("\n I am in main :\n");
	   System_flush();
	/* Create a Clock Instance */
    Clock_Params clkParams;

    /* Initialise Clock Instance with time period and timeout (system ticks) */
    Clock_Params_init(&clkParams);
    clkParams.period = 1;
    clkParams.startFlag = TRUE;

    /* Instantiate ISR for tone generation  */
	Clock_create(clk_SWI_Generate_DTMF, TIMEOUT, &clkParams, NULL);

    /* Instantiate 8 parallel ISRs for each of the eight Goertzel coefficients */
	Clock_create(clk_SWI_GTZ_0697Hz, TIMEOUT, &clkParams, NULL);

	/* Start SYS_BIOS */
    BIOS_start();
}

/*
 *  ====== clk0Fxn =====
 *  Dual-Tone Generation
 *  ====================
 */
void clk_SWI_Generate_DTMF(UArg arg0)
{
	static int tick;


	tick = Clock_getTicks();

	//sample = (int) 32768.0*sin(2.0*PI*freq1*TICK_PERIOD*tick) + 32768.0*sin(2.0*PI*freq2*TICK_PERIOD*tick);
	sample = (int) 32768.0*sin(2.0*PI*697*TICK_PERIOD*tick) + 32768.0*sin(2.0*PI*freq2*TICK_PERIOD*tick);
sample = sample >>8;
}

/*
 *  ====== clk_SWI_GTZ =====
 *  gtz sweep
 *  ====================
 */
void clk_SWI_GTZ_0697Hz(UArg arg0)
{
   	static int N = 0;
   	static int Goertzel_Value = 0;

   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	int prod1, prod2, prod3;

   	short input, coef_1;

   	coef_1 = coef[0];
    input = (short) (sample);

// to be completed

    	prod1 = (delay_1*coef_1)>>14;
    	delay = input + (short)prod1 - delay_2;
    	delay_2 = delay_1;
    	delay_1 = delay;
    	N++;

    	if (N==206){
    		prod1 = (delay_1 * delay_1);
    		prod2 = (delay_2 * delay_2);
    		prod3 = (delay_1 * coef_1)>>14;
    		prod3 = prod3 * delay_2;
    		Goertzel_Value = (prod1 + prod2 - prod3) >> 15;
    		Goertzel_Value <<= 4;
    		N = 0;
    		delay_1 = delay_2 = 0;
    	}
    	gtz_out[0] = Goertzel_Value;

}

void clk_SWI_Find_Result(UArg arg0)
{
	char result;
		int no_of_results = 0;
		if (gtz_out[0] > 50){
			if (gtz_out[4] > 50){
				result = '1';
				no_of_results++;
			} if (gtz_out[5]>50){
				result = '2';
				no_of_results++;
			} if (gtz_out[6]>50){
				result = '3';
				no_of_results++;
			} if (gtz_out[7]>50){
				result = 'A';
				no_of_results++;
			}

		} if (gtz_out[1] > 50){
			if (gtz_out[4] > 50){
				result = '4';
				no_of_results++;
			} if (gtz_out[5]>50){
				result = '5';
				no_of_results++;
			} if (gtz_out[6]>50){
				result = '6';
				no_of_results++;
			} if (gtz_out[7]>50){
				result = 'B';
				no_of_results++;
			}

		} if (gtz_out[2] > 50){
			if (gtz_out[4] > 50){
				result = '7';
				no_of_results++;
			} else if (gtz_out[5]>50){
				result = '8';
				no_of_results++;
			} else if (gtz_out[6]>50){
				result = '9';
				no_of_results++;
			} else {
				result = 'C';
				no_of_results++;
			}

		} if (gtz_out[3] > 50){
			if (gtz_out[4] > 50){
				result = '*';
				no_of_results++;
			} if (gtz_out[5]>50){
				result = '0';
				no_of_results++;
			} if (gtz_out[6]>50){
				result = '#';
				no_of_results++;
			} if (gtz_out[7]>50){
				result = 'D';
				no_of_results++;
			}

		}


		if (no_of_results == 0){
			System_printf("An error has occurred, no digit found");
			System_flush();
		} else if (no_of_results > 1){
			System_printf("An error has occurred, multiple digits found");
			System_flush();
		} else {
			System_printf("%c", result);
			System_flush();
		}
}
