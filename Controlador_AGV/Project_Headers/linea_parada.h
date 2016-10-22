/*
 * parada.h
 *
 *  Created on: Feb 3, 2016
 *      Author: Jorge Armando
 */

#ifndef PARADA_H_
#define PARADA_H_

#include "PE_Types.h"
#include "controlador_AGV.h"

#define SEGUIR	0
#define DETENER	1

bool linea_de_parada(void);
void estados_linea(void);
void inicializar_parada(void);


#endif /* PARADA_H_ */
