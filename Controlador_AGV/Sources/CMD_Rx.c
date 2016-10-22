/*
 * CMD_Rx.c
 *
 *  Created on: Feb 17, 2016
 *      Author: Jorge Armando
 */


#include "CMD_Rx.h"

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
#include "estados.h"


bool short_;
bool long_;
bool edge;
bool no_cmd_rcvd;
byte pos_actual, pos_sig, pos_prev;
cmdIR_t cmd;
byte count, state;

typedef struct _bufnode{
	cmdIR_t cmd;
	struct _bufnode* next;
	byte size;
}bufnode;

typedef struct{
	bufnode* head;
	bufnode* tail;
	byte elementos;
}RingBuffer;


bufnode buffer[BUF_SIZE];
RingBuffer buf;

void encolar_cmd(cmdIR_t* cmd);

/*bool recibir_cmd(cmdIR_t *cmd){
	byte count  = 0;
	bool error = FALSE;
	byte state = START;
	word time;
	
	no_cmd_rcvd = FALSE;
	short_ = FALSE;
	long_ = FALSE;
//	edge = FALSE;

	do{
//		FC161_Reset();
		while(!edge){	//  Esperar un pulso o espacio
//			FC161_GetTimeUS(&time);		//TODO: comentar si se usara sensor de linea
//			if(time >= 2000){
//				no_cmd_rcvd = TRUE;
//				return FALSE;
//			}
		}
		edge = FALSE;
		
		switch(state){
			case START:
				cmd->payload = 1;
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
					(cmd->payload) <<= 1;
					(cmd->payload) &= 0xFFFE;
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
					(cmd->payload) <<= 1;
					(cmd->payload) |= 0x0001;
					count++;
					state = MID1;
					short_ = FALSE;
					if(count == TAM_TRAMA){
						while(!edge);
						edge = FALSE;
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
					(cmd->payload) <<= 1;
					(cmd->payload) |= 0x0001;
					count++;
					state = MID1;
					long_ = FALSE;
					if(count == TAM_TRAMA){
						while(!edge);
						edge = FALSE;
					}
				}
				else{
					error = TRUE;
				}
				break;
				
			case START0:
				if(short_){
					(cmd->payload) <<= 1;
					(cmd->payload) &= 0xFFFE;
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
	
	if(count < TAM_TRAMA)
		return FALSE;
	
	return TRUE;
	
}*/

// signo dice hacia que lado ir, cantidad de intersecciones que hay que pasar (sin contar primera ni ultima)
int interpretar_cmd(cmdIR_t cmd){
	int retval = 0;
	int sign;
	int actual, prev, sig;
	byte act_x, act_y, sig_x, sig_y, prev_x, prev_y;
	if(cmd.fields.id == SELF_ID){
		switch(cmd.fields.cmd){
			case POS_ACTUAL:
				pos_actual = cmd.fields.payload;
				break;
			case POS_SIG:
				pos_sig = cmd.fields.payload;
				actual = (int)pos_actual;
				prev = (int)pos_prev;
				sig = (int)pos_sig;
//				sign = (actual-prev)*(sig-actual);	//sign < 0 para izq
				act_x = (pos_actual & MASK_X) >> SHIFT_X;
				act_y = (pos_actual & MASK_Y) >> SHIFT_Y;
				sig_x = (pos_sig & MASK_X) >> SHIFT_X;
				sig_y = (pos_sig & MASK_Y) >> SHIFT_Y;
				prev_x = (pos_prev & MASK_X) >> SHIFT_X;
				prev_y = (pos_prev & MASK_Y) >> SHIFT_Y;
				
					//una de las restas sera cero, la otra sera la diferencia entre
					//la posicion actual y la sigiente (sin signo). Resto 1 para
					//no contar la ultima interseccion
//				retval = abs(act_x - sig_x) + abs(act_y - sig_y);
				
//				if(sign < 0)
//					retval = -retval;
//				
//				if((act_x == sig_x && act_x == prev_x) || (act_y == sig_y && act_y == prev_y))
//					retval = 0;
				
				if(act_x == sig_x){
					if(prev_x == act_x)
						sign = 0;
					else if((prev_x < act_x && act_y > sig_y) || (prev_x > act_x && act_y < sig_y))
						sign = -1;
					else
						sign = 1;
				}
				else{
					if(prev_y == act_y)
						sign = 0;
					else if((prev_y < act_y && act_x < sig_x) || (prev_y > act_y && act_x > sig_x))
						sign = -1;
					else
						sign = 1;
				}
				retval = sign;
				pos_prev = pos_actual;
				break;
//			case STOP:
//				detener();
//				break;
//			case UTURN:
//				girar_180();
//				break;
//			case GO:
//				inicializar_motores();
//				break;
//			case P:
//				break;
//			case I:
//				break;
//			case D:
//				break;
//			case TIMEOUT:
//				break;
//			case DIST_OBS:
//				break;
//			case IZQ:
//				girar_izq();
//				break;
//			case DER:
//				girar_der();
//				break;
//			case AHEAD:
//				break;
//			case ID:
//				break;
		}
	}
	
	return retval;
}

void estados_cmd(void){
	
	if(no_cmd_rcvd){
		state = START;
		count = 0;
		no_cmd_rcvd = FALSE;
	}
	
	switch(state){
		case START:
			cmd.payload = 1;	
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
				(cmd.payload) <<= 1;
				(cmd.payload) &= 0xFFFE;
				count++;
				state = MID0;
				long_ = FALSE;
			}
			else{
				state = START;
				count = 0;
			}
			break;
			
		case START1:
			if(short_){
				(cmd.payload) <<= 1;
				(cmd.payload) |= 0x0001;
				count++;
				state = MID1;
				short_ = FALSE;
			}
			else{
				state = START;
				count = 0;
			}
			break;
			
		case MID0:
			if(short_){
				state = START0;
				short_ = FALSE;
			}
			else if(long_){
				(cmd.payload) <<= 1;
				(cmd.payload) |= 0x0001;
				count++;
				state = MID1;
				long_ = FALSE;
			}
			else{
				state = START;
				count = 0;
			}
			break;
			
		case START0:
			if(short_){
				(cmd.payload) <<= 1;
				(cmd.payload) &= 0xFFFE;
				count++;
				state = MID0;
				short_ = FALSE;
			}
			else{
				state = START;
				count = 0;
			}
			break;
	}
	
	if(count == TAM_TRAMA){
		encolar_cmd(&cmd);
		state = START;
		count = 0;
	}
}

void inicializar_recepcion(void) {
	
	byte i;
	
	for (i = 0; i < BUF_SIZE-1; i++) {
		buffer[i].next = &buffer[(i+1)%BUF_SIZE];
		buffer[i].size = 0;
	}
		
	buf.head = buffer;
	buf.tail = buffer;
	buf.elementos = 0;
		
	state = START;
	count = 0;
}

bool cmd_disponible(void) {
	return buf.elementos != 0;
}
bool recibir_cmd(cmdIR_t *cmd) {
	cmd->payload = buf.head->cmd.payload;
	buf.head = buf.head->next;
	buf.elementos--;
	return TRUE;
}
void encolar_cmd(cmdIR_t* cmd) {
	buf.tail->cmd.payload = cmd->payload;
	buf.elementos++;
	
	if(buf.tail->cmd.fields.cmd == POS_ACTUAL || buf.tail->cmd.fields.cmd == STOP){
		val_parada(TRUE);
	}
	
	buf.tail = buf.tail->next;
	
}
