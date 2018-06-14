///////////////////////////////////////////////////////////////////////
//                          MANUFACTURA FLEXIBLE Y ROBÓTICA          //
//                                                                   //
//  El objetivo del código es probar las comunicaciones UART         //
//////////////////////////////////////////////////////////////////////

//--------------------------PREAMBULO-------------------------------------//
#include<16f877a.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#fuses HS, NOWDT, NOPROTECT, NOLVP
#use delay(clock = 20MHz)
#use RS232(baud = 115200, XMIT = PIN_C6, RCV = PIN_C7, PARITY = N, STOP = 1)
//------------------------------------------------------------------------//


#BYTE TRISC = 0x87 //TRISC

#bit TRISC7 = TRISC.7
#bit TRISC6 = TRISC.6

//------------------------MAIN-------------------------------------------//
void main()
{
    set_tris_C(0x00);
    TRISC6 = 1;         //PIN_C7 has the TX PIN

    char i;

    while(TRUE)
    {
        output_high(PIN_C0);
        
        if(kbhit())        
        {
            output_low(PIN_C0);
            i = getc();
        }
        
        putc(i);
    }

}

