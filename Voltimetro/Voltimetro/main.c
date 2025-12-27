/*
 * Voltimetro.c
 *
 * Created: 18/04/2025 17:19:07
 * Author : Matheus Nifocci
 */ 

#include "voltmeter.h"

int main(void)
{
	DDRD |= 0xFC; // configura os pinos PD2 a PD7 como saída
	DDRB |= 0x3F; // configura os pinos PB0 a PB5 como saída
	DDRC &=~ (1<<DDC0); // no PORT DDRC seta o pino DDC0 como entrada (canal do ADC)
	
	uint16_t int_value = 0;
	
	InitADC(); 
		
    while (1) 
    {
		Dsp_Multiplex(Get_mV_Value(int_value, CANAL_0));		
    }
}

