#include <wiringPi.h>
#include <stdio.h>

// PWM with wiringPi library and C in order to blink an LED at a given frequency

int main(){
    const int LED= 26;

    if (wiringPiSetup() == -1) {
        printf ("Setup wiringPi Failed!\n");
        return 100;
    }

    printf ("Reminder: this program must be run with sudo. Wait for 5 seconds.\n");
    delay (5000);
    printf ("starting now.\n");
    pinMode (LED, PWM_OUTPUT);
    // set the PWM mode to Mark Space
    pwmSetMode(PWM_MODE_MS);
    // set the clock divisor to reduce the 19.2 Mhz clock
    // to something slower, 5 Khz.
    // Range of pwmSetClock() is 2 to 4095.
    pwmSetClock (3840);  	// divisor. pwm clock 19.2 Mhz divided by 3840 is 5 Khz.
    // set the PWM range which is the value for the range counter
    // which is decremented at the modified clock frequency.
    // in this case we are decrementing the range counter 5,000
    // times per second since the clock at 19.2 Mhz is being
    // divided by 3840 to give us 5 Khz.
    pwmSetRange (10000);  // range is 5000 counts to give us one second.

    delay (1);   // delay a moment to let hardware settings settle.

	int i;
	int list[] = {1250, 2500, 3750, 5000, -1};

	for (i = 0; list[i] > 0; i++) {
		// range for the value written is 0 to 1024.
		pwmWrite (LED, list[i]);  // set the Duty Cycle for this range.
		// delay 10 seconds to watch the LED flash due to the PWM hardware.
		printf (" PWM Duty Cycle %d\n", list[i]);
		delay (10000);
	}

    // pinMode(LED, INPUT);
    // digitalWrite (LED, LOW);

    return 0;
}