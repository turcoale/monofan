#include <hidef.h>
#include "derivative.h"
#include "S08_Flash.h"

byte data = ' ';

void main(void) 
{
   /* Port F Bit 1 active when error occurs */
   PTFDD |= 0x01;
   PTFD |= 0x01;

   EnableInterrupts;

   flash_init();
  
   copyinRAM();                       /* Copy flash routine to RAM */
  
   if (flash_erase( 0xF800))          /* Erase flash sector */
      PTFD &= ~0x01;
   if (flash_program( 0xF800, data))  /* Program single byte*/
      PTFD &= ~0x01;
  
  for( ; ; ) {
    __RESET_WATCHDOG();

  }  /* Loop always */
}