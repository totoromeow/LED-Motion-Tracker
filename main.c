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
    unsigned int adc_value1; // variable to hold ADC result C0
    unsigned int adc_value2; // C1
    unsigned int adc_value3; // C2
    unsigned int adc_value4; // C3
    unsigned int adc_value5; // C4
 

    DDRD = 0xff; //set PORTD for LED output
    PORTD = 0x00; // out put low - pull up resistance
    
    DDRB = 0xff;
    PORTB = 0x00;

    DDRC = 0x00; //set PORTF for analog input
    PORTC = 0x00;



    //set up analog convertor
    ADCSRA =(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
    // left ajusted - only read in 8 bits

    // interatively checking ADC output and turn on corresponding LEDs
    for(;;)
    {
    
        ADMUX = (1<<REFS0)|(1<<ADLAR);//C0

                ADCSRA |= (1<<ADSC);
        //wait until conversion completes; ADSC = 0 means complete
        while (ADCSRA & (1<<ADSC));
            adc_value2 = ADCH; //store ADC result
             if (adc_value2 >55)
             {
                PORT_ON(PORTD,0);
                PORT_ON(PORTD,1);
            }
            else
            {
                PORT_OFF(PORTD,0);
                PORT_OFF(PORTD,1);

            }
        
        ADMUX = (1<<REFS0)|(1<<ADLAR)|(1<<MUX0); //C1

                ADCSRA |= (1<<ADSC);
        //wait until conversion completes; ADSC = 0 means complete
        while (ADCSRA & (1<<ADSC));
            adc_value2 = ADCH; //store ADC result
             if (adc_value2 >55)
             {
                PORT_ON(PORTD,2);
                PORT_ON(PORTD,3);

            }
            else
            {
                PORT_OFF(PORTD,2);
                PORT_OFF(PORTD,3);

            }
        
        ADMUX = (1<<REFS0)|(1<<ADLAR)|(1<<MUX1); //C2

                ADCSRA |= (1<<ADSC);
        //wait until conversion completes; ADSC = 0 means complete
        while (ADCSRA & (1<<ADSC));
            adc_value3 = ADCH; //store ADC result
             if (adc_value3 >55)
             {
                PORT_ON(PORTD,4);
            }
            else
            {
                PORT_OFF(PORTD,4);
            }            
 
         ADMUX = (1<<REFS0)|(1<<ADLAR)|(1<<MUX1)|(1<<MUX0); //C3

                ADCSRA |= (1<<ADSC);
        //wait until conversion completes; ADSC = 0 means complete
        while (ADCSRA & (1<<ADSC));
            adc_value4 = ADCH; //store ADC result
             if (adc_value4 >55)
             {
                PORT_ON(PORTD,5);
                PORT_ON(PORTD,6);
            }
            else
            {
                PORT_OFF(PORTD,5);
                PORT_OFF(PORTD,6);
            }
 
         ADMUX = (1<<REFS0)|(1<<ADLAR)|(1<<MUX3); //C4

                ADCSRA |= (1<<ADSC);
        //wait until conversion completes; ADSC = 0 means complete
        while (ADCSRA & (1<<ADSC));
            adc_value5 = ADCH; //store ADC result
             if (adc_value5 >55)
             {
                PORT_ON(PORTD,7);
                PORT_ON(PORTB,0);
            }
            else
            {
                PORT_OFF(PORTD,4);
                PORT_OFF(PORTB,0);
            }
    
    
    }

}

         
    
