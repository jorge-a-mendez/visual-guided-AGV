/*
 * errores.c
 *
 *  Created on: Mar 30, 2016
 *      Author: Jorge Armando
 */

#include "errores.h"

#include "ERROR.h"
#include "PE_Types.h"

void error_occured(error err){
	ERROR_PutVal((byte) ~err);
}

void left_waiting(void){
	ERROR_PutVal(0x7);
}
