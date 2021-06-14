
#include "io.h"
#include <stdio.h>
#include "system.h"                 // for QSYS parameters
#include "sys/alt_irq.h"            // for IRQ support
// create standard embedded type definitions
typedef   signed char   sint8;        // signed 8 bit values
typedef unsigned char   uint8;        // unsigned 8 bit values
typedef   signed short  sint16;       // signed 16 bit values
typedef unsigned short  uint16;       // unsigned 16 bit values
typedef   signed long   sint32;       // signed 32 bit values
typedef unsigned long   uint32;       // unsigned 32 bit values
typedef         float   real32;       // 32 bit real values

unsigned char* keysBase_ptr = (unsigned char *) PUSHBUTTONS_BASE;
unsigned char* switchBase_ptr = (unsigned char *) SWITCHES_BASE;
uint32* ServoBase_ptr = (uint32 *) SERVO_COMPONENT_0_BASE;
unsigned char* HEX5Base_ptr = (unsigned char *) HEX5_BASE;
unsigned char* HEX4Base_ptr = (unsigned char *) HEX4_BASE;
unsigned char* HEX3Base_ptr = (unsigned char *) HEX3_BASE;
unsigned char* HEX2Base_ptr = (unsigned char *) HEX2_BASE;
unsigned char* HEX1Base_ptr = (unsigned char *) HEX1_BASE;
unsigned char* HEX0Base_ptr = (unsigned char *) HEX0_BASE;

int pushbutton_flag = 0;
int servo_flag = 0;
int register_value;
int maxVal;
int minVal;
int switchVal;

int hexValues[11] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x7F};
int hundreds, tens, ones;

void pushbutton_isr(void){
    register_value = *(keysBase_ptr + 12);    //read in the register value to see which button is pressed
    switchVal = *switchBase_ptr;
    if(4 == register_value){                  //if key2 was pressed(max values)
        maxVal = switchVal;
    }

    else if(8 == register_value){             //if key3 was pressed(min values)
        minVal = switchVal;
    }
    *(keysBase_ptr + 12) = 0x01; //clear interrupt flag
    return;
}

void servo_isr(void){
    static int irrelevant = 1;
    if(1 == irrelevant){
      *(ServoBase_ptr + 1) = ((5000/9) * maxVal + 25000);
      irrelevant = 0;
    }
    else{
      *(ServoBase_ptr) = ((5000/9) * minVal + 25000);
      irrelevant = 1;
    }
    return;
}

void hexDisplay(){

    tens = (minVal / 10) % 10;
    ones = minVal % 10;

    *HEX5Base_ptr = hexValues[tens];
    *HEX4Base_ptr = hexValues[ones];

    hundreds = (maxVal / 100) % 10;
    tens = (maxVal / 10) % 10;
    ones = maxVal % 10;

    *HEX2Base_ptr = hexValues[hundreds];
    *HEX1Base_ptr = hexValues[tens];
    *HEX0Base_ptr = hexValues[ones];

}

int main()
{
  maxVal = 135;
  minVal = 45;
  hexDisplay();
  *(keysBase_ptr + 8) = 0x0C; //enables pushbutton interrupt
  *(keysBase_ptr + 12) = 0x01; //clear interrupt flag

  alt_ic_isr_register(PUSHBUTTONS_IRQ_INTERRUPT_CONTROLLER_ID, PUSHBUTTONS_IRQ, pushbutton_isr, 0, 0);
  alt_ic_isr_register(SERVO_COMPONENT_0_IRQ_INTERRUPT_CONTROLLER_ID, SERVO_COMPONENT_0_IRQ, servo_isr, 0, 0);


  while (1)
  {

    hexDisplay();

  }

  return(0);
}
