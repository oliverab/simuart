/*
 * File:   newmain.c
 * Author: Oliver
 *
 * Created on 12 August 2023, 21:19
 * 
 * Demonstration of communication with the MPLAB X simulator console
 * 
 * To enable UART I/O it must be turned on in the project settings
 * 
 * To send data to the simulation a stimulus line is needed:
 * Select the "Register Injection tab:
 * Label:   "Input"   Any valid label will do
 * Reg/Var: set it to RCREG
 * Trigger: Message
 * PC Value: 0x0 or blank, probably ignored
 * Width: 2 probably ignored#
 * Data filename: select input.txt or your input file
 * Wrap: Yes      I do not know what this does
 * Format: Pkt      Required for serial emulation
 * 
 * ALSO SELECT THE GREEN "PLAY" BUTTON "Apply Synchronous Stimulus"
 * It has a blue rectangle around it when selected
 * 
 * input.txt stimulus file
 * 
 * wait 4 ms
 * "Microchip"
 * 0D 0A
 * wait 1000 ms
 *
 * Program performs a minimum of initialisation, no I/O pin settings and no baud setting as the
 * simulation does not use these.
 * 
 */

#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

#include <xc.h>

/* 
 * include standard I/O to give us access to printf
 * 
 * This isn't really needed for a trivial example like this but would be invaluable for
 * dumping out state in a more serious application
 * 
 */

#include <stdio.h>

void putch(char data) {
    while( ! PIR1bits.TXIF)          // wait until the transmitter is ready
        continue;
    TXREG = data;                     // send one character
}
void init_uart(void) {
    TXSTAbits.TXEN = 1;               // enable transmitter
    RCSTAbits.SPEN = 1;               // enable serial port
}

int main(void) {
    char last;
    init_uart();
    printf("\n");
    printf("XC8 compiler version %.2f\n", __XC8_VERSION / 1000.0f);
    printf("Test of output to simulator\n");
    RCSTAbits.CREN=1;
    while(1)
    {
        while(!PIR1bits.RCIF);
//        if (RCSTA & 0x06)
//        {
//            RCSTAbits.CREN=0;
//            RCSTAbits.CREN=1;
//        
//        }
        last=RCREG;
        if (!last) break;
        TXREG=last;
    }
        // loop forever, set a breakpoint here to terminate the simulation
    printf("End of Test of output to simulator\n");
    _delay(1000);//this is needed for the final newline to be captured
    while(1); // set breakpoint here
    return(0);
}
