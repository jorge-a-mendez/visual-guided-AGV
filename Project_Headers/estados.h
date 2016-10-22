/*
 * estados.h
 *
 *  Created on: Feb 2, 2016
 *      Author: Jorge Armando
 */

#ifndef ESTADOS_H_
#define ESTADOS_H_

#include "PE_Types.h"

#define	OBSTACULO		0
#define	LINEA_NEGRA		1
#define INIT_PID		2
#define	PID				3
#define	TOT_MEDIDAS		(100/3)	//ACTUALIZADOR_ESTADOS/MUESTREADOR

void muestrear_sensores(void);
void nuevo_estado(void);
void inicializar_variables(void);
void death(void);
void val_parada(bool val);

#endif /* ESTADOS_H_ */
