/* ###################################################################
**     Filename    : Events.c
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
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"


/* User includes (#include below this line is not maintained by Processor Expert) */




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

#include "pruebas.h"
extern bool actualizar_estado, leer_sensor;
extern bool short_, long_, edge, parada;
extern bool no_cmd_rcvd;
word values[100], i;
bool PRIMERA;

void Actualizador_Estados_OnInterrupt(void)
{
  /* Write your code here ... */
	actualizar_estado = TRUE;

}

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
void Muestreador_OnInterrupt(void)
{
  /* Write your code here ... */
	
	leer_sensor = TRUE;
}

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
void IRRx_OnCapture(void)
{
  /* Write your code here ... */
	if(PRIMERA){
		PRIMERA = FALSE;
		return;
	}
		

	IRRx_GetCaptureValue(&(values[i]));

	IRRx_Reset();
	edge = TRUE;
	
	if(MIN_SHORT <= values[i] && values[i] <= MAX_SHORT){
		short_ = TRUE;
	}
	else if(MIN_LONG <= values[i] && values[i] <= MAX_LONG){
		long_ = TRUE;
	}
	
	i++;
	i = i % 100;
	
	estados_cmd();
	IRRx_Watchdog_Reset();
	
	(void)TPM1SC;
	/* TPM1SC: TOF=0 */
	clrReg8Bits(TPM1SC, 0x80U);          /* Reset overflow interrupt request flag */ 
}




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
void IRRx_Watchdog_OnOverflow(void)
{
  /* Write your code here ... */
	no_cmd_rcvd = TRUE;
}


/* END Events */

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
