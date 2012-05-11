//*****************************************//
// file name: main.c                       //
// description: ADC -> LED Motion Tracker  //
// author: Anqi Chen                       //
// author: Mayank Prasad                   //
// language: C                             //                    
// device: ATmega168                       //
// compiler: gcc                           //
//*****************************************// 
#include <avr/io.h>

#define PORT_ON(port,pin) port |=(1 << pin)
#define PORT_OFF(port,pin) port &= ~(1 << pin) 


void adc_init()
{
    // AREF = AVcc, left ajusted ADC value
    ADMUX = (1<<REFS0)|(1<<ADLAR);

    // ADC Enable and prescaler of 128
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}


uint16_t adc_read(uint8_t ch)
{
    // selectes the corresponding channel 0~4
    // ANDing with '4' will always keep the value
    // of 'ch' between 0 and 4
    ch &= 0b00000100;   // AND operation with 4
    ADMUX = (ADMUX & 0xF8)|ch;        //clears he bottom 3 bits before ORing

    // start single conversion
    ADCSRA |= (1<<ADSC);

    // wait for conversion to complete
    // in which case ADSC will become '0'
    while(ADCSRA & (1<<ADSC));

    return(ADC);
}



int main(void)
{
    uint16_t adc_result0, adc_result1, adc_result2, adc_result3, adc_result4;      

    DDRD = 0xff; //set PORTD for LED output
    PORTD = 0x00; // output low - pull up resistance
    
    DDRB = 0xff; //set PORTB for LED output 
    PORTB = 0x00; // output low - pull up resistance

    //initialize adc
    adc_init();

    while(1)
    {
        adc_result0 = adc_read(0); //read adc value at PC0
        adc_result1 = adc_read(1);
        adc_result2 = adc_read(2);
        adc_result3 = adc_read(3);
        adc_result4 = adc_read(4);

        //condition for LED to be on
        if (adc_result0 > 200)
        {
            PORT_ON(PORTD,0);
            PORT_ON(PORTD,1);
        }
        else
        {
            PORT_OFF(PORTD,0);
            PORT_OFF(PORTD,1);
        }


        if (adc_result1 > 200)
        {
            PORT_ON(PORTD,2);
            PORT_ON(PORTD,3);
        }
        else
        {
            PORT_OFF(PORTD,2);
            PORT_OFF(PORTD,3);
        }


        if (adc_result2 > 200)
            PORT_ON(PORTD,4);
        else
            PORT_OFF(PORTD,4);



        if (adc_result3 > 200)
        {
            PORT_ON(PORTD,5);
            PORT_ON(PORTD,6);
        }
        else
        {
            PORT_OFF(PORTD,5);
            PORT_OFF(PORTD,6);
        }


        if (adc_result0 > 200)
        {
            PORT_ON(PORTD,7);
            PORT_ON(PORTB,0);
        }
        else
        {
            PORT_OFF(PORTD,7);
            PORT_OFF(PORTB,0);
        }
    }
}
