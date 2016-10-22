/*
 * CMD_Rx.h
 *
 *  Created on: Feb 3, 2016
 *      Author: Jorge Armando
 */

#ifndef CMD_RX_H_
#define CMD_RX_H_

#include "PE_Types.h"

#define TAM_TRAMA	14
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

typedef union{
	unsigned int payload;
	struct{
		byte id			:2;
		byte cmd		:4;
		byte payload	:7;
	}fields;
}cmdIR_t;



typedef enum{
	POS_ACTUAL, POS_SIG, STOP, UTURN, GO, P, I, D, 
	TIMEOUT,DIST_OBS, IZQ, DER, AHEAD, ID
};

void inicializar_recepcion(void);
bool cmd_disponible(void);
bool recibir_cmd(cmdIR_t *cmd);
int interpretar_cmd(cmdIR_t cmd);
void estados_cmd(void);

#endif /* CMD_RX_H_ */
