/*
 *  ======== util.c ========
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

#define threshold 1000

UInt32 time1, time2;

char digit;

int freq1, freq2;
int mag1, mag2;

int sample, gtz_out[8];

short coef[8] = {0x6D02, 0x68AD, 0x63FC, 0x5EE7, 0x4A70, 0x4090, 0x3290, 0x23CE}; // goertzel coefficients



void task1_dtmfDetect(void)
{

	int i, a1=0, a2=0, f1=0, f2=0;
	char dig;

	while (1) {

		dig = ' ';

		while(dig!='0'&&dig!='1'&&dig!='2'&&dig!='3'&&dig!='4'&&dig!='5'&&dig!='6'&&dig!='7'&&dig!='8'&&dig!='9'&&dig!='*'&&dig!='#'&&dig!='A'&&dig!='B'&&dig!='C'&&dig!='D')
		{
			System_printf("Enter a key press:\n");
			System_flush();
			dig = getchar();
			getchar();
		}

		if(dig == '0'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1335;
		}
		else if(dig == '1'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1209;
		}
		else if(dig == '2'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1335;
				}
		else if(dig == '3'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1477;
				}
		else if(dig == '4'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1209;
				}
		else if(dig == '5'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1335;
				}
		else if(dig == '6'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1477;
				}
		else if(dig == '7'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1209;
				}
		else if(dig == '8'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1335;
				}
		else if(dig == '9'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1477;
				}
		else if(dig == '*'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1209;
				}
		else if(dig == '#'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1477;
				}
		else if(dig == 'A'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1633;
				}
		else if(dig == 'B'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1633;
				}
		else if(dig == 'C'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1633;
				}
		else if(dig == 'D'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1633;
				}
		else{
			mag1 = 00000.0, mag2 = 00000.0, freq1 = 000, freq2 = 0000;
		}

		/*	 1. write a code that keep reading the value of "digit" from the keyboard and set the magnitude for mag1 = mag2= 32768.0 and the frequencies freq1 and freq2 according the digit value as:
			 in case when the wrong digit is entered, set: the mag1 = 00000.0, mag2 = 00000.0, freq1 = 000 and freq2 = 0000


						 '0' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1335
						 '1' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1209,
						 '2' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1335,
						 '3' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1477,
						 '4' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1209,
						 '5' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1335,
						 '6' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1477,
						 '7' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1209,
						 '8' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1335,
						 '9' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1477,
						 '*' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1209,
						 '#' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1477,
						 'A' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1633,
						 'B' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1633,
						 'C' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1633,
						 'D' : mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1633,
						otherwise : mag1 = 00000.0, mag2 = 00000.0, freq1 = 000, freq2 = 0000  */
		System_printf("About to sleep \n");
		System_flush();

		Task_sleep(500);

		// 2. Read the GTZ for each frequency and take a decision on which key has been pressed and print it.
	    a1=0, a2=0, f1=0, f2=0;

	    System_printf("\n The 0th GTZ is %d\n", gtz_out[0]);
	    System_printf("\n The 1st GTZ is %d\n", gtz_out[1]);
	    System_printf("\n The 2nd GTZ is %d\n", gtz_out[2]);
	    System_printf("\n The 3rd GTZ is %d\n", gtz_out[3]);
	    System_printf("\n The 4th GTZ is %d\n", gtz_out[4]);
	    System_flush();


	}
}


