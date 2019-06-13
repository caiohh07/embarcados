/* ###################################################################
**     Filename    : main.c
**     Project     : projeto
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-06-10, 11:19, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "DA1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	//int out = 1241; equivalente a 1,0 V no pino PTE30 - 3,3 V / 4096 = 0,806 mV por degrau */
	
	int coef = 11; // VALOR RETIRADO DO SITE DO FILTRO
	uint16_t IN; /* declara uma variável de 16 bits unsigned */
	uint16_t IN_vec[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //vetor de coef elementos
	int coef_vec[11] = {-1748, 757, 5515, 4768, -3767, 23494, -3767, 4768, 5515, 757, -1748}; //VETOR DE INTEIROS PARA A PRINCIPIO SER MAIS RAPIDO E FACIL

		/*
		coef_vec[0] = -1748; coef_vec[1] = 757; coef_vec[2] = 5515;
		coef_vec[3] = 4768; coef_vec[4] = -3767; coef_vec[5] = 23494;
		coef_vec[6] = -3767; coef_vec[7] = 4768; coef_vec[8] = 5515;
		coef_vec[9] = 757; coef_vec[10] = -1748;
		*/
	
	//uint16_t saida_vec[11] = {0,0,0,0,0,0,0,0,0,0};
	uint16_t saida;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;) {
	  int i=0;
	  int k=0;
	  for(i=coef-i; i>0; i--)
		  IN_vec[i] = IN_vec[i-1];
	  (void)AD1_Measure(TRUE); /* faz a conversão e espera pelo resultado */
	  (void)AD1_GetValue16(&IN); //Coloca o valor em IN
	  IN_vec[0] = IN;/* coloca o resultado no vetor */
	  for(k=0; k<coef; k++)
		  saida+=IN_vec[k]*coef_vec[k];
	  DA1_SetValue(DA1_DeviceData, saida);	  
		  
	  
  }
	  
		  
	
	  //DA1_SetValue(DA1_DeviceData, saida[i]);	  
	  //PENSAR COMO IMPLEMENTAR O FILTRO!!!!
	  //(void)AD1_Measure(TRUE); /* faz a conversão e espera pelo resultado */
	  //(void)AD1_GetValue16(&IN); /* coloca o resultado na variável */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
