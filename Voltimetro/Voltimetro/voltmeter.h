/*
 * voltmeter.h
 *
 * Created: 01/05/2025 09:44:05
 *  Author: Matheus Nifocci
 */ 


#ifndef VOLTMETER_H_
#define VOLTMETER_H_

	#define F_CPU 16000000UL

	#include <avr/io.h>
	#include <util/delay.h>

	#define  REF_VCC (1<<REFS0) // VCC como referência
	#define  REF_11V (1<<REFS1)| (1<<REFS0) // 1.1V como Vref

	#define ADC_EN (1<<ADEN) //enable ADC

	/*******************PRESCALER - DIVISAO DO CLOCK ***********************/
	#define DIV_2   (1<<ADPS0)
	#define DIV_4   (1<<ADPS1)
	#define DIV_8   (1<<ADPS1) | (1<<ADPS0)
	#define DIV_16  (1<<ADPS2)
	#define DIV_32  (1<<ADPS2) | (1<<ADPS0)
	#define DIV_64  (1<<ADPS2) | (1<<ADPS1)
	#define DIV_128 (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)
	/**********************************************************************/

	#define ADC_START (1<<ADSC) // Inicia conversão
	
	enum Canal_ADC
	{
		CANAL_0,
		CANAL_1,
		CANAL_2,
		CANAL_3,
		CANAL_4,
		CANAL_5,
	};

	void Dsp_Show_Number(uint8_t num, uint8_t point); // função para mostrar valor no display, com ou sem ponto
	void Dsp_Multiplex(int value); // função para multiplexar os displays
	void InitADC(); // inicializa o ADC
	uint16_t ReadADC(uint8_t canal_ADC); // lê o valor do ADC
	uint16_t Get_mV_Value(uint16_t show_value, uint8_t Canal_ADC); // converte a leitura do ADC para mostrar no display

#endif /* VOLTMETER_H_ */