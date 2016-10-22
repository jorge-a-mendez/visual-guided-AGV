/* ###################################################################
**     Filename    : Events.h
**     Project     : Controlador_AGV
**     Processor   : MC9S08QE128CLK
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2016-02-06, 10:12, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Right_Motor.h"
#include "Left_Motor.h"
#include "Right_Motor_Ref.h"
#include "Left_Motor_Ref.h"
#include "Sensores.h"
#include "Parada.h"
#include "Muestreador.h"
#include "Actualizador_Estados.h"
#include "IRRx.h"
#include "IRRx_Watchdog.h"
#include "ERROR.h"


#define MIN_SHORT	(174)		//444us at 160ns per tick
#define MAX_SHORT	(524)		//1333
//#define MIN_SHORT (310)
//#define MAX_SHORT (375)

#define MIN_LONG	(525)		//1334
#define MAX_LONG	(873)		//2222
//#define MIN_LONG (650) 
//#define MAX_LONG (730)


void Actualizador_Estados_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  Actualizador_Estados_OnInterrupt (module Events)
**
**     Component   :  Actualizador_Estados [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Muestreador_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  Muestreador_OnInterrupt (module Events)
**
**     Component   :  Muestreador [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void IRRx_OnCapture(void);
/*
** ===================================================================
**     Event       :  IRRx_OnCapture (module Events)
**
**     Component   :  IRRx [Capture]
**     Description :
**         This event is called on capturing of Timer/Counter actual
**         value (only when the component is enabled - <Enable> and the
**         events are enabled - <EnableEvent>.This event is available
**         only if a <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void IRRx_Watchdog_OnOverflow(void);
/*
** ===================================================================
**     Event       :  IRRx_Watchdog_OnOverflow (module Events)
**
**     Component   :  IRRx_Watchdog [Capture]
**     Description :
**         This event is called if counter overflows (only when the
**         component is enabled - <Enable> and the events are enabled -
**         <EnableEvent>.This event is available only if a <interrupt
**         service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
