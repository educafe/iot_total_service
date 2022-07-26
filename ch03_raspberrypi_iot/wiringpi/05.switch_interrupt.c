/*
 * Simple test the wiringPi functions of interrupt to modify the speed of led on/off
 */
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#define BUTTON_PIN 25


// Simple sequencer data
//      Triplets of LED, On/Off and delay

uint8_t data [] =
{
          0, 1, 
          1, 1, 
  0, 0,   2, 1, 
  1, 0,   3, 1, 
  2, 0,   4, 1, 
  3, 0,   5, 1, 
  4, 0,   6, 1, 
  5, 0,   7, 1, 
  6, 0, 
  7, 0, 

// Back again

          7, 1, 
          6, 1, 
  7, 0,   5, 1, 
  6, 0,   4, 1, 
  5, 0,   3, 1, 
  4, 0,   2, 1, 
  3, 0,   1, 1, 
  2, 0,   0, 1, 
  1, 0, 
  0, 0, 

  9, 9,       // End marker

} ;

volatile int speed = 100;
static int state;

void myInterrupt(void) {
	int i;
	for(i=0; i<1000000; i++) ;
	if(digitalRead(BUTTON_PIN) != state){	
		if (state) {
			if(speed < 10)
				speed = 100;
			else
				speed = speed - 10;
			dprintf(1,"Speed = %d\n", speed);
		}
	}
}

int main (void){
	int pin ;
	int dataPtr ;
	int l, s;
	
	printf ("Raspberry Pi wiringPi LED test program with interrupt\n") ;
	
	if (wiringPiSetup () == -1)
		exit (1) ;
	
	for (pin = 0 ; pin < 8 ; ++pin)
		pinMode (pin, OUTPUT) ;
	
	pinMode (BUTTON_PIN, INPUT) ;
	pullUpDnControl(BUTTON_PIN, PUD_UP);
	
	if (wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) < 0 ) {
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
		return 1;
	}
	
	/* if (wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &myInterrupt) < 0 ) {
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
		return 1;
	} */
	
	dataPtr = 0 ;
	state = digitalRead (BUTTON_PIN);
	
	for (;;) {
		l = data [dataPtr++] ;      // LED
		s = data [dataPtr++] ;      // State
		// d = data [dataPtr++] ;      // Duration (10ths)
	
		if ((l + s) == 18)		{
			dataPtr = 0 ;
			continue ;
		}
	
		digitalWrite (l, s) ;
		delay (speed) ;  
	}
	
	return 0 ;
}