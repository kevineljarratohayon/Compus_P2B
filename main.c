#include <xc.h>

#include "tad_altavoz.h"
#include "tad_timer.h"
#include "tad_SIO.h"
#include "tad_lcd.h"
#include "tad_controller.h"
#include "tad_adc.h"
#include "tad_eeprom.h"

#pragma config OSC = HSPLL //Convertimos el cristal externo de 10MHz en 40MHz
#pragma config PBADEN = DIG
#pragma config MCLRE = ON
#pragma config DEBUG = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config WDT = OFF
#pragma config LVP = OFF

//Definicion de la interrupcion de alta prioridad
void __interrupt(high_priority) RSI_High(void) {
	if(INTCONbits.TMR0IF == 1) RSI_Timer0(); // Si se ha producido una interrupción por overflow del Timer0
}

void config_interrupts(void) {
	RCONbits.IPEN = 0; // Deshabilitamos las interrupciones por prioridad
	INTCONbits.GIE = 1; // Habilitamos las interrupciones globales
	INTCONbits.PEIE = 1; // Habilitamos las interrupciones periféricas
}

void config_ports(void) {
    TI_Init();
	teclado_init();
    controllerInit();
	altavoz_init();
    marquesinaInit();
    adc_init();
	initSIO();
    hora_init();
    EEPROMinit();
	LcInit(2, 16);
    LcClear();
}

void main(void) {
    //TRISAbits.TRISA3 = 0;
	config_interrupts();
    config_ports();
    
    LcCursorOff();
    
    /*Recording r;
    r.index[0] = 'a';
    r.index[1] = 'a';
    r.index[2] = 'a';
    r.index[3] = 'a';
    r.index[4] = 'a';
    r.index[5] = 'a';
    r.index[6] = 'a';
    r.index[7] = 'a';
    r.index[8] = 'a';
    r.index[9] = 'a';
    r.timestamp[0] = 'X';
    r.timestamp[1] = 'X';
    r.timestamp[2] = 'X';
    r.timestamp[3] = 'X';
    r.timestamp[4] = 'X';
    
    
    setTimestamp(r.timestamp);
    setIndex(r.index);
    saveRecording();*/
    loadRecordings();
    
    while(1) {
        
		tecladoMotor();
        altavozMotor();
        controllerMotor();
        marquesinaMotor();
        adcMotor();
        horaMotor();
        SIOmotor();
        motorEEPROM();
	}		
}