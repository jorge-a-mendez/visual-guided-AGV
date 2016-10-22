/*
 * posicion.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jorge Armando
 */

#include "posicion.h"

#include "Cpu.h"
#include "Events.h"
#include "Right_Motor.h"
#include "Left_Motor.h"
#include "Right_Motor_Ref.h"
#include "Left_Motor_Ref.h"
#include "IRRx.h"
#include "Sensores.h"
#include "Parada.h"
#include "Muestreador.h"


int der, izq;

//valor negativo: estoy a la derecha de la linea
//valor positivo: estoy a la izquierda de la linea
int leer_posicion(void){
	byte derecha, izquierda;

//	Sensores_Measure();		//si se hace una sola lectura para todos los sensores, pasar a esa funcion.
	Sensores_GetChanValue8(BOBINA_DER, &derecha);
	Sensores_GetChanValue8(BOBINA_IZQ, &izquierda);
	
	derecha &= 0xF0;
	izquierda &= 0xF0;
	der = (int)derecha;
	izq=(int)izquierda;
	
	der = (der-DER_MIN)*100/DER_MAX;
	izq = (izq-IZQ_MIN)*100/IZQ_MAX;
	
	return der - izq;
}
