/*
 * ADC.cpp
 *
 * Created: 11/02/2024 15:06:41
 * Author : Luis Mi CONTROLLIUM
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include "ADC.h"

int main(void)
{
    cli();
	
	DDRB |= (1<<PINB5);
	PORTB &=~ (1<<PINB5);
	Start_ADC();
	
	sei();
	
    while (1) 
    {	
		float Value_ADC = (Return_ADC(0)*5.0f)/1024.0f;//se activara pb5 si adc0 supera 3.0v
		// adc=(voltaje de entrada * 1024)/ voltaje de referencia.
		if (Value_ADC < 3.2f)
		{
			PORTB |= (1<<PINB5);
		}else
		{
			PORTB &=~ (1<<PINB5);
		}
    }
	return 0;
}

void Start_ADC()
{
	//Ajustar a la derecha toda la salida
	ADMUX &=~ (1<<ADLAR);
	
	//Ajustar el voltaje de referencia al AVCC
	ADMUX |= (1<<REFS0);
	ADMUX &=~ (1<<REFS1);
	
	//divisor de frecuencias 16 Mhz /128 = 125Khz, suponiendo que use cristal externo de 16 mhz. 20-200khz
	ADCSRA |= (1<<ADPS0);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
}
int Return_ADC(int canal)
{
	//selectional el canal del adc
	ADMUX &=~ 0b11110000;
	ADMUX |= canal;
	//encendemos el adc
	ADCSRA |= (1<<ADEN);
	//espera de 10 micros
	_delay_us(10);
	//mandamos el muetreo
	ADCSRA |= (1<<ADSC);
	//esperamos a que muestree leyendo el flag
	while (!(ADCSRA & (1<<ADIF)));
	ADCSRA |= (1<<ADIF);
	//apagamos el ADC
	ADCSRA &=~ (1<<ADEN);
	
	return ADC;
	
}

