/*
 * source.c
 *
 *  Created on: Jan 16, 2024
 *      Author: HThBao
 * System time use IRQ of system Timer
 * The LED 7 Segment show Real time
 */
#include <stdio.h>
#include "io.h"
#include "system.h"
#include "altera_avalon_timer_regs.h"
#include "sys/alt_irq.h"
#include <stdbool.h>
//Variable for timer
unsigned int counter_sec = 0;
unsigned int counter_min = 0;
unsigned int counter_hour = 0;
unsigned int state_stop = 0;

//Variable for hex and switch
unsigned short *sec0, *sec1, *min0, *min1, *hour0, *hour1, *sw;

//Flag update to led 7 segment
volatile int update_display_flag = 0;

//Decode for Led 7 Segment
unsigned char segcode[] = {
		0xC0, // 0
		0xF9, // 1
		0xA4, // 2
		0xB0, // 3
		0x99, // 4
		0x92, // 5
		0x82, // 6
		0xF8, // 7
		0x80, // 8
		0x90  // 9
	};

unsigned int previous_switch_state = 0;

unsigned int timer_period_50Mhz = 50000000;
unsigned int timer_period_5Mhz = 5000000;
unsigned int current_timer_period;
void timer_Init(unsigned int period){
	current_timer_period = period ;
	// Stop Timer
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);

	IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, period);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, (period >> 16));
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
									ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | // Continue counting mode
									ALTERA_AVALON_TIMER_CONTROL_ITO_MSK | // Interrupt enable
								ALTERA_AVALON_TIMER_CONTROL_START_MSK);// Start Timer
}


void Timer_IRQ_Handler(void* isr_context){
    counter_sec++;
    if(counter_sec == 60){
        counter_sec = 0;
        counter_min++;
        if(counter_min == 60){
            counter_min = 0;
            counter_hour++;
            if(counter_hour == 24){
                counter_hour = 0;
            }
        }
    }
    update_display_flag = 1;

	// Clear Timer interrupt bit
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE,
								ALTERA_AVALON_TIMER_STATUS_TO_MSK);
}
void clear_led_7_segment()
{
	unsigned char clear_led = 0xFF;
		IOWR(HEX0_BASE, 0, clear_led);
		IOWR(HEX1_BASE, 0, clear_led);
		IOWR(HEX2_BASE, 0, clear_led);
		IOWR(HEX3_BASE, 0, clear_led);
		IOWR(HEX4_BASE, 0, clear_led);
		IOWR(HEX5_BASE, 0, clear_led);
}

void update_display()
{
	*sec0 = segcode[counter_sec%10];
	*sec1 = segcode[counter_sec/10];
	*min0 = segcode[counter_min%10];
	*min1 = segcode[counter_min/10];
	*hour0 = segcode[counter_hour%10];
	*hour1 = segcode[counter_hour/10];
}

// Stop Timer
void stop_timer() {
    // Stop Timer
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
    state_stop = 1;
    printf("Timer stopped.\n");
}

// Continute Timer
void continute_timer() {
	timer_Init(current_timer_period);
	state_stop = 0;
    printf("Timer continute.\n");
}

// Reset Timer and Counters
void reset_timer() {
    counter_sec = 0;
    counter_min = 0;
    counter_hour = 0;
    update_display_flag = 1; // Force update display after reset
    printf("Timer reset.\n");
}

// Increase speed by reducing timer period
void increase_speed() {
	current_timer_period = timer_period_5Mhz;
	if(!state_stop) timer_Init(current_timer_period);
    printf("Speed increased 10x.\n");
}
// Setup speed back timer period 50Mhz
void normal_speed() {
	current_timer_period = timer_period_50Mhz;
	if(!state_stop) timer_Init(current_timer_period);
    printf("Speed back normaly 50Mhz.\n");
}

// Check Switch states and perform actions
void check_switches() {
    unsigned int switch_state = *sw; // Read the current state of the switches

    // Detect rising edge for each switch
    if ((switch_state & 0x1) && !(previous_switch_state & 0x1)) {
        // Rising edge of SW0: Reset the timer
        reset_timer();
    }

    if ((switch_state & 0x2) && !(previous_switch_state & 0x2)) {
        // Rising edge of SW1: Stop the timer
        stop_timer();
    }

    if ((switch_state & 0x4) && !(previous_switch_state & 0x4)) {
        // Rising edge of SW2: Increase timer speed
        increase_speed();
    }


    // Detect falling edge for each switch
    if (!(switch_state & 0x2) && (previous_switch_state & 0x2)) {
        // Falling edge of SW1: Continue the timer
        continute_timer();
    }

    if (!(switch_state & 0x4) && (previous_switch_state & 0x4)) {
        // Falling edge of SW2: Restore timer speed to normal
        normal_speed();
    }

    // Update the previous switch state for the next iteration
    previous_switch_state = switch_state;
}

int main(){
	//Initialize pointers
	sec0 = (unsigned short *)HEX0_BASE;
	sec1 = (unsigned short *)HEX1_BASE;
	min0 = (unsigned short *)HEX2_BASE;
	min1 = (unsigned short *)HEX3_BASE;
	hour0 = (unsigned short *)HEX4_BASE;
	hour1 = (unsigned short *)HEX5_BASE;
	sw = (unsigned short *) SW_BASE;
	//Init for timer
	timer_Init(timer_period_50Mhz);
	alt_ic_isr_register(0, TIMER_0_IRQ, Timer_IRQ_Handler, (void*)0,(void*)0);
	//clear led 7 segment
	clear_led_7_segment();

	//More function
	while(1)
	{
		check_switches();
		if(update_display_flag)
		{
			update_display();
			printf("Real time: %2d : %2d : %2d \n", counter_hour,counter_min,counter_sec);
			update_display_flag = 0;
		}
	}

}
