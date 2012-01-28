//*****************************************//
// file name: main.c                       //
// description: ADC -> LED Motion Tracker  //
// author: Anqi Chen                       //
// language: C                             //
// Programmer: avr109                      //
// device: ATmega32u4                      //
// compiler: gcc                           //
//*****************************************//

#include <avr/io.h>
#define PORT_ON(port,pin) port|=(1 << pin)
#define PORT_OFF(port,pin) port &= ~(1 << pin)

int main(void)
{
    unsigned int adc_value;//variable to hold ADC result
    
    DDRD = 0xff; //set PORTD for LED output
    PORTD = 0x00; // out put high
    DDRF = 0x00; //set PORTF for analog input
    PORTF = 0x00; 

    //set up analog convertor
    ADCSRA =(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
    ADMUX = (1<<REFS0)|(1<<ADLAR)|(1<<MUX2);
    // left ajusted - only read in 8 bits
    //analog input port ADC 4 - F4 
    for(;;)
    {
        PORT_ON(PORTD,5);
        //keeps D5 on
        
        ADCSRA |= (1<<ADSC);
        //wait until conversion completes; ADSC = 0 means complete
            while (ADCSRA & (1<<ADSC));
        adc_value = ADCH;   //store ADC result
        if (adc_value < 205 )
        {
            PORT_ON(PORTD,4);
        }
        else
        {
            PORT_OFF(PORTD,4);
        }
    }
} 

