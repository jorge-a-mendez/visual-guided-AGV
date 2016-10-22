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

int dir_giro;
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
//	byte intersecciones;
	
//	estado = seleccionar_estado();
//	parada = FALSE;
//	
//	switch(estado){
//	case SEGUIR:
//		break;
//	case DETENER:
//		detener();
//		while(!cmd_disponible() && !(recibir_cmd(&cmd) && cmd.fields.cmd == POS_ACTUAL));

//		while(!cmd_disponible() && !recibir_cmd(&cmd) && cmd.fields.cmd == POS_SIG));
////do thing that tells where to go
//	}
	
	/*Si linea negra no sirve, comentar todo lo de arriba y descomentar siguiente*/
	detener();
//	if(!recibir_cmd(&cmd) || !(cmd.fields.id == SELF_ID) || !(cmd.fields.cmd == STOP)){
//		death();
//	}
	
	while(!cmd_disponible()){
		error_occured(WAITING_ON_POS_ACT);
	}
	left_waiting();
	if(recibir_cmd(&cmd) && cmd.fields.cmd == POS_ACTUAL){
		interpretar_cmd(cmd);
	}
	else if(cmd.fields.cmd == STOP){
		while(!cmd_disponible()){
			error_occured(WAITING_ON_POS_ACT);
		}
		left_waiting();
		if(recibir_cmd(&cmd) && cmd.fields.cmd == POS_ACTUAL){
			interpretar_cmd(cmd);
		}
		else{
			error_occured(ERR_WRONG_CMD_POS_ACT);
			death();
		}
	}
	else {
		error_occured(ERR_WRONG_CMD_STOP);
		death();
	}
	
//	while(!(cmd_disponible() && recibir_cmd(&cmd) && (cmd.fields.cmd == POS_ACTUAL || cmd.fields.cmd == STOP)));
//	if(cmd.fields.cmd == STOP)
//		while(!(cmd_disponible() && recibir_cmd(&cmd) && cmd.fields.cmd == POS_ACTUAL));
//	(void)interpretar_cmd(cmd);
//	while(!(cmd_disponible() && recibir_cmd(&cmd) && cmd.fields.cmd == POS_SIG));
//	dir_giro = interpretar_cmd(cmd);
	
	while(!cmd_disponible()){
		error_occured(WAITING_ON_POS_SIG);
	}
	left_waiting();
	if(recibir_cmd(&cmd) && cmd.fields.cmd == POS_SIG){
		dir_giro = interpretar_cmd(cmd);	// en este caso solo me interesara el signo
		if(dir_giro == DERECHA){
			girar_derecha();
		}
		else if(dir_giro == IZQUIERDA){
			girar_izquierda();
		}
		else if(dir_giro == U_TURN){
			girar_180();
		}
		//else no hago nada (sigo derecho)
		ignorar_linea = TRUE;
		detener();
	}
	else{
		error_occured(ERR_WRONG_CMD_POS_SIG);
		death();
	}
	val_parada(FALSE);
	leer_sensor = FALSE;
}

//de ser necesario, esta funcion debe recibir comando de la camara y determinar
//si lo observado fue efectivamente una linea negra o no.
//La idea seria seguir derecho y detenerse en caso de recibir algun comando,
//de lo contrario ignorar.
//byte seleccionar_estado(void){
//	byte estado;
//	
//	if(ignorar_linea){		//justo despues del giro el AGV debe encontrar una linea negra...ignorar
//		estado = SEGUIR;
//		ignorar_linea = FALSE;
//	}
//	else if(primera_linea){
//		estado = SEGUIR;
//		primera_linea = FALSE;
//	}
//	else if(giro_obstaculo){
//		pos_prev = pos_sig;	// cambio de sentido
//		estado = DETENER;
//	}
//	else if(intersecciones >= 0){
//		intersecciones--;
//		primera_linea = TRUE;
//		estado = SEGUIR;
//		giro_obstaculo = FALSE;
//	}
//	else{
//		estado = DETENER;
//	}
//	return estado;
//}

void inicializar_parada(void){
	cmdIR_t cmd;
	primera_linea = TRUE;
	ignorar_linea = FALSE;	
	pos_actual = 0;	//inicializara pos_prev en 0
	edge = FALSE;
	
	while(!cmd_disponible()){
		error_occured(WAITING_ON_POS_ACT);
	}
	left_waiting();
	if(recibir_cmd(&cmd) && cmd.fields.cmd == POS_ACTUAL){
		interpretar_cmd(cmd);
	}
	else{
		error_occured(ERR_WRONG_CMD_POS_ACT);
		death();
	}
	
	while(!cmd_disponible()){
		error_occured(WAITING_ON_POS_SIG);
	}
	left_waiting();
	if(recibir_cmd(&cmd) && cmd.fields.cmd == POS_SIG){
		(void)interpretar_cmd(cmd);
	}
	else{
		error_occured(ERR_WRONG_CMD_POS_SIG);
		death();
	}

	ignorar_linea = TRUE;	//si se inicia encima de linea negra, hay que ignorar esa primera
	val_parada(FALSE);
}
