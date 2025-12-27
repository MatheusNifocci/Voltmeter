

/*
 * voltmeter.c
 *
 * Created: 01/05/2025 09:43:41
 *  Author: Matheus Nifocci
 */
 
#include "voltmeter.h"

float vin_value;

uint16_t adc_convertion;

uint8_t numeros [10] = {
	
	0x3F, // 0  0011 1111
	0x06, // 1  0000 0110
	0x5B, // 2  0101 1011
	0x4F, // 3  0100 1111
	0x66, // 4  0110 0110
	0x6D, // 5  0110 1101
	0x7D, // 6  0111 1101
	0x07, // 7  0000 0111
	0x7F, // 8  0111 1111
	0x6F  // 9  0110 1111
	
};

void Dsp_Show_Number(uint8_t num, uint8_t point){
	
	uint8_t value = numeros[num];
	
	PORTD = (PORTD & 0x03) | (value << 2);
	
	if(value & 0x40) { // logia é para validar que o bit 7 esta setado
		PORTB |= (1<<PORTB0);
	}
	else{
		PORTB &= ~(1<<PORTB0);
	}
	
	if (point) {
		PORTB |= (1 << PORTB1);  // liga o ponto
	}
	else {
		PORTB &= ~(1 << PORTB1); // desliga o ponto
	}
}

void Dsp_Multiplex(int value){
	
	
	uint8_t d0 = value / 1000;
	uint8_t d1 = (value / 100) % 10;
	uint8_t d2 = (value / 10) % 10;
	uint8_t d3 = value % 10;
	
	PORTB |= ~(1<<PORTB5);
	Dsp_Show_Number(d0,1);
	_delay_ms(5);
	PORTB &= (1<<PORTB5);
	
	
	PORTB |= ~(1<<PORTB4);
	Dsp_Show_Number(d1,0);
	_delay_ms(5);
	PORTB &= (1<<PORTB4);
	
	
	PORTB |= ~(1<<PORTB3);
	Dsp_Show_Number(d2,0);
	_delay_ms(5);
	PORTB &= (1<<PORTB3);
	
	
	PORTB |= ~(1<<PORTB2);
	Dsp_Show_Number(d3,0);
	_delay_ms(5);
	PORTB &= (1<<PORTB2);
}


void InitADC()// função de inicialização do ADC
{
	ADMUX  |= REF_VCC; //seta o registrador REFSO com 1 e faz logica OU com o registrador de configuração do ADMUX
	
	ADCSRA |= ADC_EN | DIV_128 ; // Seta o registrador ADCSRA (habilita o ADC e usa o fator de 128 para dividir o clock)
}


uint16_t ReadADC(uint8_t canal_ADC) // função para leitura do canal do ADC
{
	ADMUX = (ADMUX & 0xF0)|(canal_ADC & 0x0F); //seleciona o canal do ADC
	ADCSRA |= ADC_START ; // inicializa a conversao
	while(ADCSRA & ADC_START); // enquanto a conversão estiver habilitada, faz a leitura do canal
	
	return ADC; // retorna o valor Rgtr ADC
}

uint16_t Get_mV_Value(uint16_t show_value, uint8_t Canal_ADC)
{
	
	adc_convertion = ReadADC(Canal_ADC);
	
	vin_value = ((adc_convertion * 5.0)/1024.0);
	
	show_value = (vin_value * 1000);
	
	return show_value;

	
}