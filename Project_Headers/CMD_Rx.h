/*
 * CMD_Rx.h
 *
 *  Created on: Feb 3, 2016
 *      Author: Jorge Armando
 */

#ifndef CMD_RX_H_
#define CMD_RX_H_

#include "PE_Types.h"
#include "errores.h"

#define TAM_TRAMA	9
#define START		0
#define	MID1		1
#define	START1		2
#define	MID0		3
#define	START0		4
#define SELF_ID		01
#define MASK_X		0x38
#define MASK_Y		0x07
#define	SHIFT_X		3
#define	SHIFT_Y		0

#define BUF_SIZE	10

#define DERECHA		0
#define IZQUIERDA	1
#define DERECHO		2
#define	U_TURN		3

typedef union{
	byte payload;
	struct{
//		byte id			:2;
		byte cmd		:2;
		byte payload	:6;
	}fields;
}cmdIR_t;



typedef enum{
	POS_ACTUAL, POS_SIG, STOP
};

void inicializar_recepcion(void);
bool cmd_disponible(void);
bool recibir_cmd(cmdIR_t *cmd);
int interpretar_cmd(cmdIR_t cmd);
bool estados_cmd(void);

#endif /* CMD_RX_H_ */
