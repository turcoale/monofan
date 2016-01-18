/** ###################################################################
**     Filename  : monofan.C
**     Project   : monofan
**     Processor : MC9S08SH8CPJ
**     Version   : Driver 01.11
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 15/01/2016, 10:43 a.m.
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE monofan */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Cap1.h"
#include "TI1.h"
#include "EInt1.h"
#include "Bit2.h"
#include "Bit1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
byte zc;
int ticks, actual;
int seg;
byte alarma;
byte mode;



byte ReadSetTime(void);
void SetDisp(byte disparo);
void Delay1s(byte segs);
byte ReadMode(void);

/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */


//valor minimo cero, valor maximo 590 ancho del pulso 31

alarma = 0;
PTCD_PTCD0 = 1;
Delay1s(5);
mode = 0;

for(;;){
SetDisp(ReadSetTime());
mode = ReadMode();


}
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END monofan */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

byte ReadSetTime(void){
ADCCFG = 0b00000000;
ADCSC1 = 0b00001011;

 while(ADCSC2_ADACT);
 while(!ADCSC1_COCO); 
         
  
 return ADCRL; 
}

void SetDisp(byte disparo) {

byte band = 0;
if(disparo == 0) {PTCD_PTCD0 = 1;
band = 1;
}
if(disparo == 255) {PTCD_PTCD0 = 0;
band = 1;
}

if(zc && !band)
{
 ticks = 0;
 while(ticks < disparo){ };
 PTCD_PTCD0 = 1;
 actual = ticks;
 while(ticks < actual + 31){ };
 PTCD_PTCD0 = 0;
 zc = 0;
 band = 0;
}

}

void Delay1s(byte segs){
  byte counter = 0;
  seg = 0;
  while(counter <= segs){
  if(seg >= 25000){
   counter++;
   seg = 0;
  }
  }



}

byte ReadMode(void){
return PTBD_PTBD6;

}
