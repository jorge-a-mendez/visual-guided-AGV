/*
 * errores.h
 *
 *  Created on: Mar 30, 2016
 *      Author: Jorge Armando
 */

#ifndef ERRORES_H_
#define ERRORES_H_

typedef enum{
	ERR_NOISE_IN_CMD = 1, ERR_WRONG_CMD_POS_SIG,
	ERR_WRONG_CMD_POS_ACT, ERR_WRONG_CMD_STOP,
	ERR_EMPTY_QUEUE, WAITING_ON_POS_ACT, WAITING_ON_POS_SIG
}error;

void error_occured(error err);
void left_waiting(void);

#endif /* ERRORES_H_ */
