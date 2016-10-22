/*
 * parada.c
 *
 *  Created on: Feb 3, 2016
 *      Author: Jorge Armando
 */

#include "linea_parada.h"

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
#include "CMD_Rx.h"
#include "estados.h"

int intersecciones;
bool primera_linea, ignorar_linea;
extern bool parada, giro_obstaculo, edge, no_cmd_rcvd;
extern bool actualizar_estado, leer_sensor;
extern byte pos_actual, pos_sig, pos_prev;

byte seleccionar_estado(void);

bool linea_de_parada(void){
	return Parada_GetVal();	//revisar si debe ser Parada o !Parada
}

void estados_linea(void){
	byte estado;
	cmdIR_t cmd;
	
//	estado = seleccionar_estado();
//	parada = FALSE;
//	
//	switch(estado){
//	case SEGUIR:
//		nuevo_estado();	//OJO: se vuelve recursivo, pensar si sirve
//		break;
//	case DETENER:
//		detener();
//		if(recibir_cmd(&cmd) && cmd.fields.id == SELF_ID && cmd.fields.cmd == POS_ACTUAL){
//			interpretar_cmd(cmd);
//		}
//		else{
//			death();
//		}
//		if(recibir_cmd(&cmd) && cmd.fields.id == SELF_ID && cmd.fields.cmd == POS_SIG){
//			intersecciones = interpretar_cmd(cmd);
//			if(intersecciones > 0){
//				girar_derecha();
//			}
//			else{
//				intersecciones = -intersecciones;
//				girar_izquierda();
//			}
//			ignorar_linea = TRUE;
//		}
//		else{
//			death();
//		}
//	}
	
	/*Si linea negra no sirve, comentar todo lo de arriba y descomentar siguiente*/
	detener();
//	if(!recibir_cmd(&cmd) || !(cmd.fields.id == SELF_ID) || !(cmd.fields.cmd == STOP)){
//		death();
//	}
	
	while(!cmd_disponible());
	if(recibir_cmd(&cmd) && cmd.fields.id == SELF_ID && cmd.fields.cmd == POS_ACTUAL){
		interpretar_cmd(cmd);
	}
	else if(cmd.fields.id == SELF_ID && cmd.fields.cmd == STOP){
		while(!cmd_disponible());
		if(recibir_cmd(&cmd) && cmd.fields.id == SELF_ID && cmd.fields.cmd == POS_ACTUAL){
			interpretar_cmd(cmd);
		}
	}
	else {
		death();
	}
	
	while(!cmd_disponible());
	if(recibir_cmd(&cmd) && cmd.fields.id == SELF_ID && cmd.fields.cmd == POS_SIG){
		intersecciones = interpretar_cmd(cmd);	// en este caso solo me interesara el signo
		if(intersecciones > 0){
			girar_derecha();
		}
		else if(intersecciones < 0){
			girar_izquierda();
		}
		ignorar_linea = TRUE;
	}
	else{
		death();
	}
	val_parada(FALSE);
	leer_sensor = FALSE;
	actualizar_estado = FALSE;
}

//de ser necesario, esta funcion debe recibir comando de la camara y determinar
//si lo observado fue efectivamente una linea negra o no.
//La idea seria seguir derecho y detenerse en caso de recibir algun comando,
//de lo contrario ignorar.
byte seleccionar_estado(void){
	byte estado;
	
	if(ignorar_linea){		//justo despues del giro el AGV debe encontrar una linea negra...ignorar
		estado = SEGUIR;
		ignorar_linea = FALSE;
	}
	else if(primera_linea){
		estado = SEGUIR;
		primera_linea = FALSE;
	}
	else if(giro_obstaculo){
		pos_prev = pos_sig;	// cambio de sentido
		estado = DETENER;
	}
	else if(intersecciones > 0){
		intersecciones--;
		primera_linea = TRUE;
		estado = SEGUIR;
		giro_obstaculo = FALSE;
	}
	else{
		estado = DETENER;
	}
	return estado;
}

void inicializar_parada(void){
	cmdIR_t cmd;
	primera_linea = TRUE;
	ignorar_linea = FALSE;	
	pos_actual = 0;	//inicializara pos_prev en 0
	edge = FALSE;
	
	while(!cmd_disponible());
	if(recibir_cmd(&cmd) && cmd.fields.id == SELF_ID && cmd.fields.cmd == POS_ACTUAL){
		interpretar_cmd(cmd);
	}
	else{
		death();
	}
	
	while(!cmd_disponible());
	if(recibir_cmd(&cmd) && cmd.fields.id == SELF_ID && cmd.fields.cmd == POS_SIG){
		intersecciones = interpretar_cmd(cmd);
	}
	else{
		death();
	}

	ignorar_linea = TRUE;	//si se inicia encima de linea negra, hay que ignorar esa primera
	val_parada(FALSE);
}
