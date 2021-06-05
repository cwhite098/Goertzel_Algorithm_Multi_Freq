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


	int i, a1=0, a2=0, f1=0, f2=0, dig;



	while (1) {

<<<<<<< Updated upstream


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


		Task_sleep(500);

		// 2. Read the GTZ for each frequency and take a decision on which key has been pressed and print it.
	    a1=0, a2=0, f1=0, f2=0;




=======
		dig = ' ';

		//loop that keeps asking for an input until a valid one is given.
		while(dig!='0'&&dig!='1'&&dig!='2'&&dig!='3'&&dig!='4'&&dig!='5'&&dig!='6'
				&&dig!='7'&&dig!='8'&&dig!='9'&&dig!='*'&&dig!='#'&&dig!='A'
						&&dig!='B'&&dig!='C'&&dig!='D')
		{
			System_printf("Enter a key press:\n");
			System_flush();
			dig = getchar();
			fseek(stdin,0,SEEK_END); //this clears the input buffer
		}

		if(dig == '0'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 941, freq2 = 1336;
		}
		else if(dig == '1'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1209;
		}
		else if(dig == '2'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1336;
				}
		else if(dig == '3'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 697, freq2 = 1477;
				}
		else if(dig == '4'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1209;
				}
		else if(dig == '5'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1336;
				}
		else if(dig == '6'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 770, freq2 = 1477;
				}
		else if(dig == '7'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1209;
				}
		else if(dig == '8'){
			mag1 = 32768.0, mag2 = 32768.0, freq1 = 852, freq2 = 1336;
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

		System_printf("Calculating GTZ values... \n");
		System_flush();

		Task_sleep(500);

	    //prints GTZ values
	    System_printf("\n The 0th GTZ is %d\n", gtz_out[0]);
	    System_printf("\n The 1st GTZ is %d\n", gtz_out[1]);
	    System_printf("\n The 2nd GTZ is %d\n", gtz_out[2]);
	    System_printf("\n The 3rd GTZ is %d\n", gtz_out[3]);
	    System_printf("\n The 4th GTZ is %d\n", gtz_out[4]);
	    System_printf("\n The 5th GTZ is %d\n", gtz_out[5]);
		System_printf("\n The 6th GTZ is %d\n", gtz_out[6]);
		System_printf("\n The 7th GTZ is %d\n", gtz_out[7]);
	    System_flush();

	    char result;
	    int no_of_results = 0;
	    int gtz_cutoff = 200000;

		if (gtz_out[0] > gtz_cutoff){
			if (gtz_out[4] > gtz_cutoff){
				result = '1';
				no_of_results++;
			} if (gtz_out[5]>gtz_cutoff){
				result = '2';
				no_of_results++;
			} if (gtz_out[6]>gtz_cutoff){
				result = '3';
				no_of_results++;
			} if (gtz_out[7]>gtz_cutoff){
				result = 'A';
				no_of_results++;
			}

		} if (gtz_out[1] > gtz_cutoff){
			if (gtz_out[4] > gtz_cutoff){
				result = '4';
				no_of_results++;
			} if (gtz_out[5]>gtz_cutoff){
				result = '5';
				no_of_results++;
			} if (gtz_out[6]>gtz_cutoff){
				result = '6';
				no_of_results++;
			} if (gtz_out[7]>gtz_cutoff){
				result = 'B';
				no_of_results++;
			}

		} if (gtz_out[2] > gtz_cutoff){
			if (gtz_out[4] > gtz_cutoff){
				result = '7';
				no_of_results++;
			} else if (gtz_out[5]>gtz_cutoff){
				result = '8';
				no_of_results++;
			} else if (gtz_out[6]>gtz_cutoff){
				result = '9';
				no_of_results++;
			} else {
				result = 'C';
				no_of_results++;
			}

		} if (gtz_out[3] > gtz_cutoff){
			if (gtz_out[4] > gtz_cutoff){
				result = '*';
				no_of_results++;
			} if (gtz_out[5]>gtz_cutoff){
				result = '0';
				no_of_results++;
			} if (gtz_out[6]>gtz_cutoff){
				result = '#';
				no_of_results++;
			} if (gtz_out[7]>gtz_cutoff){
				result = 'D';
				no_of_results++;
			}
		}

		if (no_of_results == 0){
			System_printf("An error has occurred, no digit found\n");
			System_flush();
		} else if (no_of_results > 1){
			System_printf("An error has occurred, multiple digits found\n");
			System_flush();
		} else {
			System_printf("You entered: %c\n", result);
			System_flush();
		}
>>>>>>> Stashed changes
	}
}

