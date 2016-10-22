/*
 * pruebas.c
 *
 *  Created on: Feb 6, 2016
 *      Author: Jorge Armando
 */

#include "pruebas.h"
#include "estados.h"
#include "motores.h"
#include "controlador_AGV.h"

#include "estados.h"
#include "Events.h"
#include "CMD_Rx.h"

#include "PE_Types.h"

extern bool obstaculo;
extern bool parada;
extern int  posicion;

extern bool actualizar_estado,leer_sensor;
extern word values[100];

void try_cmd_rcv(){
	byte count  = 0;
	word i = 0, cmd;
	bool error = FALSE;
	byte state = START;
	bool short_ = FALSE;
	bool long_ = FALSE;

	do{
		if(MIN_SHORT <= values[i] && values[i] <= MAX_SHORT){
			short_ = TRUE;
		}
		else if(MIN_LONG <= values[i] && values[i] <= MAX_LONG){
			long_ = TRUE;
		}
		i++;
		
		switch(state){
			case START:
				cmd = 1;
				count++;
				state = MID1;
				short_ = FALSE;
				long_ = FALSE;
				break;
				
			case MID1:
				if(short_){
					state = START1;
					short_ = FALSE;
				}
				else if(long_){
					cmd <<= 1;
					cmd &= 0xFFFE;
					count++;
					state = MID0;
					long_ = FALSE;
				}
				else{
					error = TRUE;
				}
				break;
				
			case START1:
				if(short_){
					cmd <<= 1;
					cmd |= 0x0001;
					count++;
					state = MID1;
					short_ = FALSE;
					if(count == TAM_TRAMA){
						i++;
					}
				}
				else{
					error = TRUE;
				}
				break;
				
			case MID0:
				if(short_){
					state = START0;
					short_ = FALSE;
				}
				else if (long_){
					cmd <<= 1;
					cmd |= 0x0001;
					count++;
					state = MID1;
					long_ = FALSE;
					if(count == TAM_TRAMA){
						i++;
					}
				}
				else{
					error = TRUE;
				}
				break;
				
			case START0:
				if(short_){
					cmd <<= 1;
					cmd &= 0xFFFE;
					count++;
					state = MID0;
					short_ = FALSE;
				}
				else{
					error = TRUE;
				}
				break;
		}
			
	}while(count < TAM_TRAMA &&  !error);
	
	short_ = FALSE;
	long_ = FALSE;
	
}

void prueba_recibir_cmd(void){
	cmdIR_t cmd[5];
	int i=0;
	while(1){
		if(recibir_cmd(cmd+i))
			i++;
		while(i == 5);
	}
}

void prueba_linea_NOsensores(void){
	velocidad_der(FWD_SPEED_RIGHT);
	velocidad_izq(FWD_SPEED_LEFT);
	while(1);
}

void prueba_girar_derecha(void){
	
	while(!actualizar_estado){
		while(!leer_sensor);
		muestrear_sensores();
		leer_sensor = FALSE;
	}
	
	actualizar_estado = FALSE;
	girar_derecha();
	prueba_linea_sensores();
}

void prueba_girar_izquierda(void){
	while(!actualizar_estado){
		while(!leer_sensor);
		muestrear_sensores();
		leer_sensor = FALSE;
	}
	
	actualizar_estado = FALSE;
	girar_izquierda();
	prueba_linea_sensores();
}

void prueba_girar_180(void){
	
	
	while(!actualizar_estado){
		while(!leer_sensor);
		muestrear_sensores();
		leer_sensor = FALSE;
	}
	
	actualizar_estado = FALSE;
	girar_derecha();
	prueba_linea_sensores();
}

void prueba_detener(void){
//	velocidad_der(FWD_SPEED_RIGHT);
//	velocidad_izq(FWD_SPEED_LEFT);
	
	while(1){		
		while(!actualizar_estado){
			while(!leer_sensor);
			muestrear_sensores();
			leer_sensor = FALSE;
		}
		actualizar_estado = FALSE;
		
		if(obstaculo)
			detener();
	}
}

void prueba_linea_sensores(void){
	//inicializar timer de sensores en processor expert
	//inicializar timer de estados en processor expert
	actualizar_estado = FALSE;
	leer_sensor = FALSE;
	posicion = 0;
	
	
	velocidad_der(FWD_SPEED_RIGHT);
	velocidad_izq(FWD_SPEED_LEFT);
	
	inicializar_motores();
	
	while(1){
		while(!actualizar_estado){
			while(!leer_sensor);
			muestrear_sensores();
			leer_sensor = FALSE;
		}
		actualizar_estado = FALSE;
		
		pid(posicion/TOT_MEDIDAS);
		posicion = 0;		//limpiar promedio para siguiente ronda de muestras
		
	}
}
