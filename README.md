# SoPC_Timer_Clock
This program aims to develop a real-time clock system capable of managing and displaying time (hours, minutes, seconds) within an FPGA environment. The system utilizes the hardware components of the DE10-Standard board, including a timer module, seven-segment LED displays for output visualization, and physical switches for controlling clock functions.


![image](https://github.com/user-attachments/assets/1f433fea-ebb2-4730-8f14-48092f79cf2f)


Figure 1. Overview of the Hardware System

The program utilizes Quartus 18.1 along with the Nios II software for execution.

* Overall Functionality
- Time Display: The clock displays real-time (hours:minutes:seconds) on six 7-segment LEDs (2 for hours, 2 for minutes, 2 for seconds).

- Control via Switches:
SW0: Resets the time to 0.
SW1: Stops (ON) or resumes (OFF) the timer.
SW2: Increases speed (ON, 5MHz) or returns to normal speed (OFF, 50MHz).
Timer Speed: Can operate at 50MHz (1 real second ≈ 1 counted second) or 5MHz (10 times faster).

- Time Update: The timer generates periodic interrupts to increment the counter and update the display.
