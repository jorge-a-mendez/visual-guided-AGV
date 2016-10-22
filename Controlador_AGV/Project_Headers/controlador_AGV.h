/*
 * pid.h
 *
 *  Created on: Feb 2, 2016
 *      Author: Jorge Armando
 */

#ifndef PID_H_
#define PID_H_

#include "motores.h"
#include "posicion.h"

#define	THRESH	5

int inicializar_motores(void);
int pid(int posicion);
bool girar_derecha(void);
bool girar_izquierda(void);
bool girar_180(void);
int detener(void);

#endif /* PID_H_ */
