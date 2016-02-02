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
#include "FLASH1.h"
#include "Bit1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "S08_Flash.h"

#define NORMAL 1
#define SETPOINT 0
#define TIMEINIT 190
#define OK 1
#define BASEDIR 0xE000;

 /** Read the contents of the Address sent as a parameter in a byte format */
  #define u8Flash_ReadByte(Address)       *(unsigned char*)Address
  
  /** Read the contents of the Address sent as a parameter in a word format */
  #define u16Flash_ReadWord(Address)       *(unsigned int*)Address

  /** Read the contents of the Address sent as a parameter in a double word format */
  #define u32Flash_ReadDoubleWord(Address) *(unsigned long*)Address

byte zc;
int ticks, actual;
int seg;
byte mode;
volatile word AD1_OutV;                /* Sum of measured values */
byte LB, HB;

static const int temp[] = {322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,321,318,315,312,309,306,303,300,297,294,291,288,285,282,279,276,273,270,267,264,261,258,255,252,249,246,243,240,237,234,231,228,225,222,219,216,213,210,207,204,201,198,195,192,189,186,183,180,177,174,171,168,165,162,159,156,153,150,147,144,141,138,135,132,129,126,123,120,117,114,111,108,105,102,99,96,93,90,87,84,81,78,75,72,69,66,63,60,57,54,51,48,45,42,39,36,33,30,27,24,21,18,15,12,9,6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

volatile unsigned char PGM[6]  = { 0xf7, 0x44, 0xf5, 0x27,0xfd, 0x81}; 

/* Array of opcode instructions of the Erase/Program function in the HCS08 family */


byte ReadInput(word *values);
byte ReadSetPoint(word *values);

void SetDisp(word disparo);
void Delay1s(byte segs);
byte ReadMode(void);
byte Flash_Erase_Page(word page);
byte Flash_Program_Byte(word address, byte data);




word interm;
word flash;

/* User includes (#include below this line is not maintained by Processor Expert) */

  

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

//Flash_Erase_Page(0xE000);
//Flash_Program_Byte(0xE002,0x03);

//valor minimo cero, valor maximo 600 ancho del pulso 31
mode = SETPOINT;


switch(mode)
{
  case NORMAL : 
  {
    PTCD_PTCD0 = 1;
    //Delay1s(TIMEINIT);
  
    for(;;){
            ReadInput(&interm);
            SetDisp(interm);
           } 
  
  }    break;
  
  case SETPOINT : 
  {
    PTCD_PTCD0 = 1;
    //Delay1s(5);
            ReadSetPoint(&interm);
            Flash_Erase_Page(0xE000);
            Flash_Program_Byte(0xE000, ADCRH);
            Flash_Program_Byte(0xE001, ADCRL);
            flash = u16Flash_ReadWord(0xE000);

    for(;;){
            //ReadSetPoint(&interm);
            SetDisp(interm);
           }
  
  }    break;
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

byte ReadInput(word *values){

ADCCFG = 0b00001000;
ADCSC1 = 0b00001010;

while(ADCSC2_ADACT);
while(!ADCSC1_COCO); 

((TWREG volatile*)(&AD1_OutV))->b.high = ADCRH; /* Save measured value */
((TWREG volatile*)(&AD1_OutV))->b.low = ADCRL; /* Save measured value */

*values = (word)((AD1_OutV));   /* Save measured values to the output buffer */
  
return OK;
}

byte ReadSetPoint(word *values){

ADCCFG = 0b00001000;
ADCSC1 = 0b00001011;

while(ADCSC2_ADACT);
while(!ADCSC1_COCO); 

((TWREG volatile*)(&AD1_OutV))->b.high = ADCRH; /* Save measured value */
((TWREG volatile*)(&AD1_OutV))->b.low = ADCRL; /* Save measured value */

*values = (word)((AD1_OutV));   /* Save measured values to the output buffer */

return OK;
}

void SetDisp(word disparo) {
byte band = 0;
word sp;

ReadSetPoint(&sp);

switch (mode)
{
  case SETPOINT:
  {
    if(disparo < 600)
  {
   ticks = 0;
   while(ticks < disparo){ };
   PTCD_PTCD0 = 1;
   actual = ticks;
   while(ticks < actual + 31){ };
   PTCD_PTCD0 = 0;
   zc = 0;
   band = 0;
  } else
     {
           PTCD_PTCD0 = 0;
           zc = 0;
           band = 0;
     }
  
  } break;
  
  case NORMAL:
  {
    if(disparo > sp  && disparo < 600)
  {
   ticks = 0;
   while(ticks < disparo){ };
   PTCD_PTCD0 = 1;
   actual = ticks;
   while(ticks < actual + 31){ };
   PTCD_PTCD0 = 0;
   zc = 0;
   band = 0;
  } else
     {
       if (disparo < 5)
         {
           PTCD_PTCD0 = 1;
           zc = 0;
           band = 0;
         }
 
       if (disparo > 600)
         {
           PTCD_PTCD0 = 0;
           zc = 0;
           band = 0;
         }
     
     }
  
  } break;

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



byte Flash_Erase_Page(word page) {

asm {            
      	TPA         ; Get status to A
        PSHA        ; Save current status
        SEI         ; Disable interrupts
        LDA  #0x30  ;
        STA  FSTAT  ;Clear FACCERR & FPVIOL flags            
	      LDHX  page  ;
	      STA ,X      ; Save the data            
	      LDA  #$40   ; Erase command
	      STA  FCMD   ;
	      LDA  #FSTAT_FCBEF_MASK ;
	      LDHX @FSTAT ;
	      JSR  PGM    ;
	      PULA        ; Restore previous status
	      TAP         ;         
    }

return (FSTAT & 0x30);  }

byte Flash_Program_Byte(word address, byte data) {        
asm {
	TPA	    ;              
	PSHA        ; Save current status              
	SEI         ; Disable interrupts
	LDA  #0x30  ;
  STA  FSTAT  ; Clear FACCERR & FPVIOL flags            
  LDHX  address;
  LDA  data   ;
  STA ,X      ; Save the data
  LDA  #$20   ; Burn command            
  STA  FCMD   ;
  LDA  #FSTAT_FCBEF_MASK ;
  LDHX @FSTAT ;
  JSR   PGM   ;
  PULA        ; Restore previous status
  TAP         
    }
return (FSTAT & 0x30);  } 
