/*
 * estados.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jorge Armando
 */

#include "estados.h"

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

#include "posicion.h"
#include "linea_parada.h"
#include "proximidad.h"
#include "controlador_AGV.h"


bool obstaculo, parada, giro_obstaculo, init_pid;
int  posicion;
byte estado;
bool actualizar_estado,leer_sensor;
extern bool no_cmd_rcvd;

void maquina_estados(void);

void maquina_estados(void){
	byte cmd;
	
	switch (estado){
		case OBSTACULO:
//			girar_180();
//			obstaculo = FALSE;
//			posicion = leer_posicion()*TOT_MEDIDAS;		//envio a hacer PID con el valor leido directamente (el parametro que entrara al PID sera posicon*TOT/TOT)
//			val_parada(FALSE);
//			inicializar_motores(); //reseteo las variables de velocidad del PID y arranco motores hacia adelante
//			nuevo_estado();		//OJO: se vuelve recursivo, pensar si sirve
//			giro_obstaculo = TRUE;
			detener();
			while(obstaculo_en_via()){
				Sensores_Measure();
			}
			obstaculo = FALSE;
			leer_sensor = FALSE;
			init_pid = TRUE;
//			inicializar_motores();
//			nuevo_estado();
			break;
		case LINEA_NEGRA:
			estados_linea();
//			if(no_cmd_rcvd){
//				val_parada(FALSE);
//			}
//			posicion = leer_posicion()*TOT_MEDIDAS;		//envio a hacer PID con el valor leido directamente (el parametro que entrara al PID sera posicon*TOT/TOT)
//			inicializar_motores(); //reseteo las variables de velocidad del PID y arranco motores hacia adelante
//			nuevo_estado();		//OJO: se vuelve recursivo, pensar si sirve
			init_pid = TRUE;
			break;
		case INIT_PID:
			posicion = leer_posicion()*TOT_MEDIDAS;
			init_pid = FALSE;
			inicializar_motores();
		case PID:
			pid(posicion/TOT_MEDIDAS);
			break;
	}
	posicion = 0;
}

void nuevo_estado(void){
	if(obstaculo){
		estado = OBSTACULO;
	}
	else if(parada){
		estado = LINEA_NEGRA;
	}
	else if(init_pid){
		estado = INIT_PID;
	}
	else{
		estado = PID;
	}
	maquina_estados();
	posicion = 0;
	actualizar_estado = FALSE;
}

void muestrear_sensores(void){
	Sensores_Measure();
	posicion += leer_posicion();
	if(!obstaculo)
		obstaculo = obstaculo_en_via();
	/*comentar si se usara la camara para deteccion de lineas*/
//	if(!parada)	//en caso de que no funcione: && edge
//		parada = linea_de_parada();
	/*------------------------------------*/
	leer_sensor = FALSE;
}

void inicializar_variables(void){
	obstaculo = FALSE;
	val_parada(FALSE);
	giro_obstaculo = FALSE;
	actualizar_estado = FALSE;
	leer_sensor = FALSE;
	init_pid = FALSE;
	inicializar_recepcion();
	inicializar_parada();
}

void death(void){
	detener();
	while(1);	
}

void val_parada(bool val){
	parada = val;
}
