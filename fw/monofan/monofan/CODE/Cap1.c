/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cap1.C
**     Project   : monofan
**     Processor : MC9S08SH8CPJ
**     Component : Capture
**     Version   : Component 02.211, Driver 01.27, CPU db: 3.00.062
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 15/01/2016, 11:48 a.m.
**     Abstract  :
**         This bean "Capture" simply implements the capture function
**         of timer. The counter counts the same way as in free run mode. On
**         the selected edge of the input signal (on the input pin), the current
**         content of the counter register is written into the capture
**         register and the OnCapture event is called.
**     Settings  :
**             Timer capture encapsulation : Capture
**
**         Timer
**             Timer                   : TPM1
**             Counter shared          : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**           Maximal time for capture register
**             Xtal ticks              : 512
**             microseconds            : 16384
**             milliseconds            : 16
**             seconds (real)          : 0.016384
**             Hz                      : 61
**           One tick of timer is
**             nanoseconds             : 250
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Capture                : TPM1C0V   [$0026]
**              Counter                : TPM1CNT   [$0021]
**              Mode                   : TPM1SC    [$0020]
**              Run                    : TPM1SC    [$0020]
**              Prescaler              : TPM1SC    [$0020]
**
**         Used input pin              : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       20            |  PTA0_PIA0_TPM1CH0_ADP0_ACMPPLUS
**             ----------------------------------------------------
**
**         Port name                   : PTA
**         Bit number (in port)        : 0
**         Bit mask of the port        : $0001
**
**         Signal edge/level           : rising
**         Priority                    : 
**         Pull option                 : off
**
**     Contents  :
**         Reset           - byte Cap1_Reset(void);
**         GetCaptureValue - byte Cap1_GetCaptureValue(Cap1_TCapturedValue *Value);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE Cap1. */

#include "Events.h"
#include "Cap1.h"




/*
** ===================================================================
**     Method      :  Cap1_Reset (component Capture)
**
**     Description :
**         This method resets the counter register (see implementation
**         note in <General Info>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte Cap1_Reset(word *Value)

**  This method is implemented as a macro. See Cap1.h file.  **
*/

/*
** ===================================================================
**     Method      :  Cap1_GetCaptureValue (component Capture)
**
**     Description :
**         This method gets the last value captured by enabled timer.
**         Note: one tick of timer is
**               250 ns in high speed mode
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Value           - A pointer to the content of the
**                           capture register
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte Cap1_GetCaptureValue(Cap1_TCapturedValue *Value)

**  This method is implemented as a macro. See Cap1.h file.  **
*/

/*
** ===================================================================
**     Method      :  Cap1_Init (component Capture)
**
**     Description :
**         Initializes the associated peripheral(s) and the bean internal 
**         variables. The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void Cap1_Init(void)
{
  /* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM1SC, 0x00);               /* Stop HW */ 
  /* TPM1MOD: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0,BIT7=0,BIT6=0,BIT5=0,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  setReg16(TPM1MOD, 0x00U);            /* Disable modulo register */ 
  /* TPM1CNTH: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0 */
  setReg8(TPM1CNTH, 0x00);             /* Reset counter */ 
  /* TPM1C0V: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0,BIT7=0,BIT6=0,BIT5=0,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  setReg16(TPM1C0V, 0x00U);            /* Clear capture register */ 
  /* TPM1SC: PS2=0,PS1=0,PS0=0 */
  clrReg8Bits(TPM1SC, 0x07);           /* Set prescaler register */ 
  /* TPM1C0SC: CH0F=0,CH0IE=1,MS0B=0,MS0A=0,ELS0B=0,ELS0A=1,??=0,??=0 */
  setReg8(TPM1C0SC, 0x44);             /* Enable both interrupt and capture function */ 
  /* TPM1SC: CLKSB=0,CLKSA=1 */
  clrSetReg8Bits(TPM1SC, 0x10, 0x08);  /* Run counter */ 
}


/*
** ===================================================================
**     Method      :  Interrupt (component Capture)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes of the bean event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(Cap1_Interrupt)
{
  (void)TPM1C0SC;                      /* Dummy read to reset interrupt request flag */
  /* TPM1C0SC: CH0F=0 */
  clrReg8Bits(TPM1C0SC, 0x80);         /* Reset interrupt request flag */ 
  Cap1_OnCapture();                    /* Invoke user event */
}



/* END Cap1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/