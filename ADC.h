/*
 * ADC.h
 *
 * Created: 11/02/2024 15:11:14
 *  Author: Luis Mi CONTROLLIUM
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <util/delay.h>

void Start_ADC();
int Return_ADC(int canal);

#endif /* ADC_H_ */