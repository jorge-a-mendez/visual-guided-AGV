#include <stdio.h>
#include <stdlib.h>

#include "motores.h"



word escalar(dword vel);

// -100<=v<=100
int velocidad_der(long vel){
	word duty_cycle;
	
	if(vel < 0){	//go backwards
		Right_Motor_Ref_SetVal();//set - pin to "1"
		vel = -vel;
		duty_cycle = ONE_HUNDRED_PWM - escalar((dword)vel);
	}
	else{
		Right_Motor_Ref_ClrVal();// set - pin to "0"
		duty_cycle = escalar((dword)vel);
	}
	
	(void)Right_Motor_SetRatio16(duty_cycle);
	return 0;
}

//-100<=v<=100
int velocidad_izq(long vel){
	
	word duty_cycle;
	
	if(vel < 0){	//go backwards
		Left_Motor_Ref_SetVal();//set - pin to "1"
		vel = -vel;
		duty_cycle = ONE_HUNDRED_PWM - escalar(vel);
	}
	else{
		Left_Motor_Ref_ClrVal();// set - pin to "0"
		duty_cycle = escalar(vel);
	}
	
	(void)Left_Motor_SetRatio16(duty_cycle);
	return 0;
}

int apagar_motores(void){
	Right_Motor_Ref_ClrVal();
	Right_Motor_SetRatio16(0);
	
	Left_Motor_Ref_ClrVal();
	Left_Motor_SetRatio16(0);
	
	return 0;
}

//escalar v entre duty cycle minimo y maximo
word escalar(dword vel){
	dword w;
	if (vel > ONE_H_PCT)
		vel = ONE_H_PCT;
	w = (vel*(MAX_DUTY_CYCLE-MIN_DUTY_CYCLE))/ONE_H_PCT + MIN_DUTY_CYCLE;
	return (word)w;
}

