/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : FLASH1.C
**     Project   : monofan
**     Processor : MC9S08SH8CPJ
**     Component : Init_FLASH
**     Version   : Component 01.044, Driver 01.13, CPU db: 3.00.062
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 01/02/2016, 08:41 a.m.
**     Abstract  :
**          This file implements the FLASH (IntFLASH) module initialization 
**          according to the Peripheral Initialization Bean settings, and defines
**          interrupt service routines prototypes. 
**     Settings  :
**          Bean name                                      : FLASH1
**          Device                                         : IntFLASH
**          Clock settings                                 : 
**            Divide flash clock by 8                      : no
**            Clock Divider                                : 20
**            Frequency (150kHz - 200kHz)                  : 200 kHz
**          Initialization                                 : 
**            Call Init method                             : yes
**     Contents  :
**         Init - void FLASH1_Init(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE FLASH1. */

#include "FLASH1.h"

/*
** ===================================================================
**     Method      :  FLASH1_Init (component Init_FLASH)
**
**     Description :
**         This method initializes registers of the FLASH module
**         according to this Peripheral Initialization Bean settings.
**         Call this method in user code to initialize the module.
**         By default, the method is called by PE automatically; see
**         "Call Init method" property of the bean for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FLASH1_Init(void)
{
  /* FSTAT: FCBEF=0,FCCF=0,FPVIOL=1,FACCERR=1,??=0,FBLANK=0,??=0,??=0 */
  setReg8(FSTAT, 0x30);                /* Clear error flags */ 
  /* FCDIV: DIVLD=0,PRDIV8=0,DIV5=0,DIV4=1,DIV3=0,DIV2=0,DIV1=1,DIV0=1 */
  setReg8(FCDIV, 0x13);                /* Set clock divider */ 
}

/* END FLASH1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/