/*
 * proximidad.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jorge Armando
 */

#include "proximidad.h"

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

bool obstaculo_en_via(void){
	byte proximidad;
//	Sensores_Measure();		//si se hace una sola lectura para todos los sensores, pasar a esa funcion.
	Sensores_GetChanValue8(PROXIMIDAD, &proximidad);
	
	return (proximidad > UMBRAL);
}
