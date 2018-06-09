//----------------------------------------------------------------------------
//                    Programa para checar qué onda con el gripper
//----------------------------------------------------------------------------

#include<16f877a.h>
#device adc = 10
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#fuses HS, NOWDT, NOPROTECT, NOLVP
#use delay(clock = 20 MHz)
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)

//--------------  PORT LABELING  -----------------------
#byte TMR0       = 0x01
#byte PORTB      = 0x06
#byte PORTC      = 0x07
#byte PORTD      = 0x08
#byte INTCON     = 0x0B
#byte OPTION_REG = 0x81
#byte TRISB      = 0x86
#byte TRISC      = 0x87
#byte TRISD      = 0x88


//------------    PIN LABELING   -----------------------
#bit TRIS_TX = TRISC.6
#bit TRIS_RX = TRISC.7
#bit TRIS_P1 = TRISC.1
#bit TRIS_P2 = TRISC.2
#bit TRISC3  = TRISC.3
#bit B1      = PORTC.3
#bit B2      = PORTD.0
#bit LED     = PORTD.2
#bit PINC7   = PORTC.7
#bit PINC6   = PORTC.6
#bit CHB     = PORTB.4
#bit CHA     = PORTB.5

// ------------------  GLOBAL VARIABLES   ------------------------
int8 CHB1;
int8 past;
int rec       = 0;
int16  i = 0;

//-----------------   FUNCTION PROTOTYPES  -----------------------
#int_rb
void rb_isr()
{
   if(past)
   {
      if(CHA^CHB1)
      {
         i+=1;

      }
      else
      {
         i-=1;

      }

   }
   else
   {
      past = 1;

   }
   CHB1 = CHB;

}


//----------------------    MAIN   --------------------------------


void main()
{
//------------------   MORE VARIABLES  -------------------------

//  Inicializar variables auxiliares --------------------
int duty       = 0;
int16 pulsos   = 0;
int8 p1        = 0;
int8 p2        = 0;


// Inicializar Regitros ---------------------------------
OPTION_REG     = 0x07;
TRISB          = 0x00;
TRISD          = 0x00;
TRIS_TX        = 1;
TRIS_RX        = 0;
setup_ccp1(CCP_PWM);
setup_timer_2(T2_DIV_BY_1,250,1);//setup_timer_2(T2_DIV_BY_16,255,1);124,4
set_pwm1_duty(0);
LED  = 1;
TMR0 = 0;


past = 0;

while(TRUE)
{
   // Mandar bandera -----------------------------
   putc(0xAA);
   pulsos = i;
   
   //Mandar parte alta ----------------------------
   p1 = (char)((pulsos & 0xFF00) >>8);
   putc(p1);
   
   //Mandar parte baja ----------------------------
   p2 = (char)(pulsos & 0x00FF);
   putc(p2);
   
   do{
   
      if(kbhit())
      {
         rec  = getch();
         duty = (0x7F & rec)<<1;
      
      if(128 & rec)
      {
          B1 = 0;
          B2 = 1;
      }
      
      else
      {
          B1 = 1;
          B2 = 0;    
      }
      set_pwm1_duty(duty);
      }// end if kbhit
      
   }while(TMR0<98);
   
   TMR0 = 0;
   
}// end while(true)
   

}// end main


