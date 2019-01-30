/*
 * init.cpp
 *
 * Created: 30.01.2019 15:26:38
 *  Author: Dmitry
 */ 

#include <avr/io.h>
#include "MB/include/mb.h"
#include "MB/include/mbport.h"
#include "include/time.h"

void initPorts() {    
    // Input/Output Ports initialization

    // Port A initialization
    // inputs
    DDRA = (0 << DDA7) | (0 << DDA6) | (0 << DDA5) | (0 << DDA4) | (0 << DDA3) | (0 << DDA2) | (0 << DDA1) | (0 << DDA0);
    PORTA = (1 << PA7) | (1 << PA6)  | (1 << PA5)  | (1 << PA4)  | (1 << PA3)  | (1 << PA2)  | (1 << PA1)  | (1 << PA0);

    // Port B initialization
    // iiiiooii
    DDRB = (0 << DDB7) | (0 << DDB6) | (1 << DDB5) | (1 << DDB4) | (0 << DDB3) | (0 << DDB2) | (0 << DDB1) | (0 << DDB0);
    PORTB = (0 << PA7) | (0 << PA6)  | (0 << PA5)  | (0 << PA4)  | (0 << PA3)  | (0 << PA2)  | (0 << PA1)  | (0 << PA0);

    // Port C initialization
    // 
    DDRC = (0 << DDC7) | (0 << DDC6) | (0 << DDC5) | (0 << DDC4) | (0 << DDC3) | (0 << DDC2) | (0 << DDC1) | (0 << DDC0);
    PORTC = (1 << PA7) | (1 << PA6)  | (1 << PA5)  | (1 << PA4)  | (1 << PA3)  | (1 << PA2)  | (1 << PA1)  | (1 << PA0);

    // Port D initialization
    // 
    DDRD = (0 << DDD7) | (0 << DDD6) | (0 << DDD5) | (1 << DDD4) | (0 << DDD3) | (0 << DDD2) | (0 << DDD1) | (0 << DDD0);
    PORTD = (1 << PA7) | (1 << PA6)  | (1 << PA5)  | (0 << PA4)  | (1 << PA3)  | (1 << PA2)  | (0 << PA1)  | (1 << PA0);

    // Port E initialization
    // inputs (spare)
    DDRE = (0 << DDE7) | (0 << DDE6) | (0 << DDE5) | (0 << DDE4) | (0 << DDE3) | (0 << DDE2) | (0 << DDE1) | (0 << DDE0);
    PORTE = 0x00;

    // Port F initialization
    // inputs
    DDRF = (0 << DDF7) | (0 << DDF6) | (0 << DDF5) | (0 << DDF4) | (0 << DDF3) | (0 << DDF2) | (0 << DDF1) | (0 << DDF0);
    PORTF = 0xFF;

    // Port G initialization
    // 
    DDRG = (0 << DDG5) | (0 << DDG4) | (0 << DDG3) | (1 << DDG2) | (0 << DDG1) | (0 << DDG0);
    PORTG = (1 << PA5) | (1 << PA4)  | (1 << PA3)  | (0 << PA2)  | (1 << PA1)  | (1 << PA0);

    // Port H initialization
    // 
    DDRH = (0 << DDH7) | (0 << DDH6) | (0 << DDH5) | (0 << DDH4) | (0 << DDH3) | (1 << DDH2) | (0 << DDH1) | (0 << DDH0);
    PORTH = (1 << PA7) | (1 << PA6)  | (1 << PA5)  | (1 << PA4)  | (1 << PA3)  | (1 << PA2)  | (0 << PA1)  | (0 << PA0);

    // Port J initialization
    // 
    DDRJ = (0 << DDJ7) | (1 << DDJ6) | (1 << DDJ5) | (0 << DDJ4) | (0 << DDJ3) | (1 << DDJ2) | (0 << DDJ1) | (0 << DDJ0);
    PORTJ = (1 << PA7) | (0 << PA6)  | (0 << PA5)  | (1 << PA4)  | (1 << PA3)  | (0 << PA2)  | (0 << PA1)  | (0 << PA0);

    // Port K initialization
    // 
    DDRK = (1 << DDK7) | (1 << DDK6) | (1 << DDK5) | (1 << DDK4) | (1 << DDK3) | (1 << DDK2) | (1 << DDK1) | (1 << DDK0);
    PORTK = 0x00;

    // Port L initialization
    // inputs (spare)
    DDRL = (0 << DDL7) | (0 << DDL6) | (0 << DDL5) | (0 << DDL4) | (0 << DDL3) | (0 << DDL2) | (0 << DDL1) | (0 << DDL0);
    PORTL = 0x00;

    // USART1 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter: On
    // USART0 Mode: Asynchronous
    // USART0 Baud Rate: 9600
    //UCSR1A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
    //UCSR1B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
    //UCSR1C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
    //UBRR1H=0x00;
    //UBRR1L=0x67;

    // USART3 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter: On
    // USART0 Mode: Asynchronous
    // USART0 Baud Rate: 9600
    //UCSR3A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
    //UCSR3B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
    //UCSR3C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
    //UBRR3H=0x00;
    //UBRR3L=0x67;
    /*
    for (uint8_t i = 0; i < QUEUE_SIZE; i++) {
        tasks.active[i] = false;
    }
    */
}

void initModbus() {
    eMBInit(MB_RTU, 0xF2, 0, 9600, MB_PAR_NONE);
    eMBEnable();
}

void initCycleTime() {
    updateCycleTime();
    resetMaxCycleTime();
}