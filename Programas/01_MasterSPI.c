//-----------------------------------------------------------------------------
//--------------------- Robótica Práctica 4: ----------------------------------
//               Comunicación SPI - Master Program
//                           versión 2.0
//                  por Alitzel López Sánchez
//-----------------------------------------------------------------------------
// Idea: 
// Utilizando SPI, hacer que el Microcontrolador A despliegue la lectura de los
// dip switches del Microcontrolador B
//----------------------------------------------------------------------------

//--------------------- PIC CONFIGURATION  ----------------------------------
#include<16f877a.h>
#include<stdlib.h>
#include<stdio.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock = 20MHz)

//------------------------ PORT LABELING  -----------------------------------
#BYTE SSPSTAT = 0x94 
#BYTE SSPBUF  = 0x13
#BYTE SSPCON  = 0x14
#BYTE OPTION  = 0x81
#BYTE TRISB   = 0x86
#BYTE TRISD   = 0x88
#BYTE TRISC   = 0x87
#BYTE PORTB   = 0x06
#BYTE PORTD   = 0x08
#BYTE PORTC   = 0x07
#BYTE TMR0    = 0x01

#BIT SSPSTAT_BF = SSPSTAT.0
#BIT RBPU       = OPTION.7
#BIT TRISC3     = TRISC.3
#BIT TRISC5     = TRISC.5
#BIT TRISC7     = TRISC.7
#BIT RC7        = PORTC.7
#BIT A  = PORTD.2
#BIT E  = PORTD.3
#BIT C  = PORTD.4
#BIT F  = PORTD.5
#BIT D  = PORTD.6

//------------------------ NEW DATA TYPES -----------------------------------
typedef enum
{
  SPI_MASTER_OSC_DIV4  = 0b00100000,
  SPI_MASTER_OSC_DIV16 = 0b00100001,
  SPI_MASTER_OSC_DIV64 = 0b00100010,
  SPI_MASTER_TMR2      = 0b00100011,
  SPI_SLAVE_SS_EN      = 0b00100100,
  SPI_SLAVE_SS_DIS     = 0b00100101
}Spi_Type;

typedef enum
{
  SPI_DATA_SAMPLE_MIDDLE = 0b00000000,
  SPI_DATA_SAMPLE_END    = 0b10000000
}Spi_Data_Sample;

typedef enum
{
  SPI_CLOCK_IDLE_HIGH = 0b00001000,
  SPI_CLOCK_IDLE_LOW  = 0b00000000
}Spi_Clock_Idle;

typedef enum
{
  SPI_IDLE_2_ACTIVE = 0b00000000,
  SPI_ACTIVE_2_IDLE = 0b01000000
}Spi_Transmit_Edge;


//----------------------  FUNCTION PROTOTYPES ------------------------------ 
void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge);
static void spiReceiveWait();
unsigned spiDataReady();
char spiRead();
void spiWrite(char dat);

//----------------------      MAIN       ------------------------------------
void main(void)
{

   TRISB  = 0x00;
   TRISD  = 0x00;
   delay_ms(1000);
   PORTD  = 0xFF;
   TRISC7 = 0;
   RC7    = 1;
   
   int c = 0;
   
   spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
   while(TRUE)
   {
      for(c = 0; c <= 4;c++)
      {
         A = 0;
         spiWrite(0xFF);
         delay_ms(1000);
         A = 1;

         E = 0;
         spiWrite(0xFF);
         delay_ms(1000);
         E = 1;     
         
         C = 0;
         spiWrite(0xFF);
         delay_ms(1000);
         C = 1;  
         
         F = 0;
         spiWrite(0xFF);
         delay_ms(1000);
         F = 1;   
         
         D = 0;
         spiWrite(0xFF);
         delay_ms(1000);
         D = 1;
      }
   }

}


//-----------------------   FUNCTION AREA ------------------------------------

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
  TRISC5 = 0;
  if(sType & 0b00000100) //If Slave Mode
  {
    SSPSTAT = sTransmitEdge;
    TRISC3 = 1;
  }
  else //If Master Mode
  {
    SSPSTAT = sDataSample | sTransmitEdge;
    TRISC3 = 0;
  }
  SSPCON = sType | sClockIdle;
}

static void spiReceiveWait()
{
  while ( !SSPSTAT_BF ); // Wait for Data Receipt complete
}

void spiWrite(char dat) //Write data to SPI bus
{
  SSPBUF = dat;
}


unsigned spiDataReady() //Check whether the data is ready to read
{
  if(SSPSTAT_BF)
    return 1;
  else
    return 0;
}

char spiRead()    // Read the received data
{
  spiReceiveWait();      // Wait until all bits receive
  return(SSPBUF); // Read the received data from the buffer
}


